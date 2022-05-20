#include "../lib/common.h"
#include "../lib/ADC.h"
#include "../lib/conversions.h"
#include "../lib/GPIO.h"
#include "../lib/program_tasks.h"
#include "../lib/PWM.h"

// ADC-converted value of potentiometer
static uint16_t _POT_value;
// ADC-converted value of light dependant resistor
static uint16_t _LDR_value;

// handle for the ADC mutex semaphore
extern xSemaphoreHandle _MUTEX_ADC;
// handle for the POT value
extern xSemaphoreHandle _MUTEX_POT;
// handle for the LDR value
extern xSemaphoreHandle _MUTEX_LDR;

// handle for the pwm task
extern TaskHandle_t _TH_setPWM;

// task handles the polling for the potentiometer value
void TASK_getPotentiometerValue(void *pvParameters)
{
    // to check for changes in the potentiometer value
    uint16_t new_POT_value = 0;
    // initialize global pot value
    _POT_value = 0;
    while (1)
    {
        if (xSemaphoreTake(_MUTEX_ADC, (TickType_t)10) == pdTRUE)
        {
            new_POT_value = ADC_read(POT_CHANNEL);
            xSemaphoreGive(_MUTEX_ADC);
            Convert_to8Bit(&new_POT_value);
            if (new_POT_value != _POT_value)
            {
                xSemaphoreTake(_MUTEX_POT, 10);
                _POT_value = new_POT_value;
                xSemaphoreGive(_MUTEX_POT);
                vTaskResume(_TH_setPWM);
            }
            portYIELD();
        }
    }
}

// task handles the polling for the LDR value
void TASK_getLDRValue(void *pvParameters)
{
    // to check for changes in the LDR value
    uint16_t new_LDR_value = 0;
    // initialize global ldr value
    _LDR_value = 0;
    while (1)
    {
        if (xSemaphoreTake(_MUTEX_ADC, (TickType_t)10) == pdTRUE)
        {
            new_LDR_value = ADC_read(LDR_CHANNEL);
            xSemaphoreGive(_MUTEX_ADC);
            Convert_to8Bit(&new_LDR_value);
            Adjust_LDR_(&new_LDR_value);
            if (new_LDR_value != _LDR_value)
            {
                xSemaphoreTake(_MUTEX_LDR, 10);
                _LDR_value = new_LDR_value;
                xSemaphoreGive(_MUTEX_LDR);
                vTaskResume(_TH_setPWM);
            }
            portYIELD();
        }
    }
}

// task handles the adjusting of the pwm
void TASK_setPWM(void *pvParameters)
{
    vTaskSuspend(_TH_setPWM);
    while (1)
    {
        // adjust the pwm according to current input
        if (xSemaphoreTake(_MUTEX_POT, (TickType_t)10) == pdTRUE)
        {
            if (xSemaphoreTake(_MUTEX_LDR, (TickType_t)10) == pdTRUE)
            {
                PWM_adjust(_POT_value - _LDR_value);
                xSemaphoreGive(_MUTEX_LDR);
            }               
            xSemaphoreGive(_MUTEX_POT);
        }
        vTaskSuspend(_TH_setPWM);
        if (xSemaphoreTake(_MUTEX_LDR, (TickType_t)10) == pdTRUE)
        {
            if (xSemaphoreTake(_MUTEX_POT, (TickType_t)10) == pdTRUE)
            {
                PWM_adjust(_POT_value - _LDR_value);
                xSemaphoreGive(_MUTEX_POT);
            }               
            xSemaphoreGive(_MUTEX_LDR);
        }
        // suspend task until next wakeup
        vTaskSuspend(_TH_setPWM);
    }
}