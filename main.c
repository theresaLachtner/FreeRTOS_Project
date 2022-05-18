#include "lib/common.h"
#include "lib/setup.h"
#include "lib/GPIO.h"
#include "lib/ADC.h"
#include "lib/dimmer.h"


#if (configUSE_IDLE_HPPK == 1)

void vApplicationIdleHook(void);

#endif

static void exampleTask(void *pvParameters);
extern TaskHandle_t exampleTaskHandle;

ISR(ADC_vect)
{
	BaseType_t xYieldRequired = xTaskResumeFromISR(exampleTaskHandle);
	portYIELD();
}

extern uint16_t _POT_value;
extern uint16_t _LDR_value;

int main () 
{
	//_delay_ms(5000);
	setup();

	xTaskCreate(exampleTask, (portCHAR*) "LED", configMINIMAL_STACK_SIZE, NULL, 2, &exampleTaskHandle);

	vTaskStartScheduler();
	
	/*while (LED_dim() == 0) 
	{

	}*/
}

static void exampleTask(void *pvParameters)
{
	while (LED_dim() == 0) {}
}

#if (configUSE_IDLE_HOOK == 1)
void vApplicationIdleHook(void)
{
	//vCoRoutineSchedule();
}
#endif
