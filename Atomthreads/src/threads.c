#include "../lib/common.h"
#include "../lib/ADC.h"
#include "../lib/conversions.h"
#include "../lib/threads.h"
#include "../lib/PWM.h"

#include <string.h>
#include <stdlib.h>

// ADC-converted value of potentiometer
static uint16_t _POT_value = 0;
// ADC-converted value of LDR
static uint16_t _LDR_value = 0;;
// mutex for handling ADC values
extern ATOM_MUTEX _MUTEX_ADC;
// queue for signaling a change in the ADC values to the PWM
extern ATOM_QUEUE _QUEUE_ADCchange;

// thread handles polling for the potentiometer value
void THREAD_getPotentiometerValue(uint32_t param)
{

    // variable to check for changes in the potentiometer value
    uint16_t new_POT_value = 0;
    _POT_value = 0;
    // message that signals a change
    uint8_t changeMSG = 1;
    // activate interrupt for ADC ready interrupt
    //ADCSRA |= (1 << ADIE);
    char str[10];
    while (1)
    {
        // take the ADC mutex
        if (atomMutexGet(&_MUTEX_ADC, 10) == ATOM_OK)
        {
            // read the currrent value from the ADC channel
            new_POT_value = ADC_read(POT_CHANNEL);

            sprintf(str, "%d", new_POT_value);
            UART_sendstring(str);
            UART_sendstring("\n\n");

            // give back the mutex
            atomMutexPut(&_MUTEX_ADC);
            // convert to PWM conform value
            Convert_to8Bit(&new_POT_value);
            // if change occured, signal the PWM thread


            

            if (new_POT_value != _POT_value)
            {
                _POT_value = new_POT_value;
                //atomQueuePut(&_QUEUE_ADCchange, 10, &changeMSG);
            }
        }
    }
}

// thread handles polling for the LDR value
void THREAD_getLDRValue(uint32_t param)
{
    // variable to check for changes in the potentiometer value
    uint16_t new_LDR_value = 0;
    _LDR_value = 0;
    // message that signals a change
    uint8_t changeMSG = 2;
    // activate interrupt for ADC ready interrupt
    ADCSRA |= (1 << ADIE);
    char str[10];
    while (1)
    {
        // take the ADC mutex
        if (atomMutexGet(&_MUTEX_ADC, 10) == ATOM_OK)
        {
            // read the currrent value from the ADC channel
            new_LDR_value = ADC_read(POT_CHANNEL);
            // give back the mutex
            atomMutexPut(&_MUTEX_ADC);
            // convert to PWM conform value
            Convert_to8Bit(&new_LDR_value);
            // adjust to value between 0 and 255
            Adjust_LDR(&new_LDR_value);

            sprintf(str, "%d", new_LDR_value);
            UART_sendstring(str);
            UART_sendstring("\n");

            // if change occured, signal the PWM thread
            if (new_LDR_value != _LDR_value)
            {
                _LDR_value = new_LDR_value;
                atomQueuePut(&_QUEUE_ADCchange, 10, &changeMSG);
            }
        }
    }
}

// thread adjusts PWM according to potentiometer and LDR
void THREAD_setPWM(uint32_t param)
{
    // variable for receiving messages
    uint8_t msg = 0;
    char str[10];
    while (1)
    {
        if (atomQueueGet(&_QUEUE_ADCchange, 100, &msg) == ATOM_OK)
        {
            atomMutexGet(&_MUTEX_ADC, 30);
            
            PWM_adjust(_POT_value - _LDR_value);
            atomMutexPut(&_MUTEX_ADC);
        }
    }
}