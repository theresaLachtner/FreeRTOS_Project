#include "lib/common.h"
#include "lib/setup.h"
#include "lib/GPIO.h"
#include "lib/ADC.h"
#include "lib/program_tasks.h"

#if (configUSE_IDLE_HOOK == 1)

void vApplicationIdleHook(void);

#endif

// task handle for get potentiometer value
extern TaskHandle_t _TH_getPOTval;
// task handle for get LDR value
extern TaskHandle_t _TH_getLDRval;
// handle for the pwm task
extern TaskHandle_t _TH_setPWM;
// handle for the ADC mutex semaphore
extern xSemaphoreHandle _MUTEX_ADC;
// current ADC-channel - global variable
extern uint16_t _ADC_channel;
// handle for the ADC ready queue
extern QueueHandle_t _QH_ADCready;

ISR(ADC_vect)
{
	// stores the recieved info from queue
	QueueMessage_t ADCready = 1;
	// send adc ready message to queue
	xQueueSend(_QH_ADCready, &ADCready, (TickType_t) 10);
	// yield remaining slice time
	portYIELD();
}

int main()
{
	// set up GPIO, ADC, initial PWM (and debugging)
	setup();

	// create mutexes
	_MUTEX_ADC = xSemaphoreCreateMutex();
	_MUTEX_POT = xSemaphoreCreateMutex();
	_MUTEX_LDR = xSemaphoreCreateMutex();

	// create message queue
	_QH_ADCready = xQueueCreate(2, sizeof(QueueMessage_t*));  


	// create the tasks
	xTaskCreate(&TASK_setPWM, (portCHAR *)"PWM", configMINIMAL_STACK_SIZE, NULL, 4, &_TH_setPWM);
	xTaskCreate(&TASK_getPotentiometerValue, (portCHAR *)"potVAL", configMINIMAL_STACK_SIZE, NULL, 3, &_TH_getPOTval);
	xTaskCreate(&TASK_getLDRValue, (portCHAR *)"ldrVAL", configMINIMAL_STACK_SIZE, NULL, 3, &_TH_getLDRval);

	// start the scheduler
	vTaskStartScheduler();
}

#if (configUSE_IDLE_HOOK == 1)
void vApplicationIdleHook(void)
{
	// vCoRoutineSchedule();
}
#endif
