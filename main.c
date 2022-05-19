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
// handle for the channel info queue
extern QueueHandle_t _QH_channelInfo;

ISR(ADC_vect)
{
	// stores the recieved info from queue
	QueueMessage_t channelInfo;
	BaseType_t taskWokenByReceive = pdFALSE;
	if (xQueueReceiveFromISR(_QH_channelInfo, &channelInfo, &taskWokenByReceive) == pdTRUE)
	{
		// check, wich task is to be resumed according to channelInfo message
		switch (channelInfo.q_channel)
		{
			case POT_CHANNEL:
				UART_sendstring("1");
				// resume potentiometer task
				xTaskNotifyFromISR(_TH_getPOTval, 0, (eNotifyAction)eNoAction, NULL);
				break;
			case LDR_CHANNEL:
				UART_sendstring("2");
				// resume LDR task
				xTaskNotifyFromISR(_TH_getLDRval, 0, (eNotifyAction)eNoAction, NULL);
				break;
			default:
				break;
		}
	}
	// yield remaining slice time
	portYIELD();
}

extern uint16_t _POT_value;
extern uint16_t _LDR_value;

int main()
{
	// set up GPIO, ADC, initial PWM (and debugging)
	setup();

	// create mutex for uninterrupted ADC conversion
	_MUTEX_ADC = xSemaphoreCreateMutex();
	// create message queue for transmitting current ADC channel
	_QH_channelInfo = xQueueCreate(2, sizeof(QueueMessage_t*));  

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
