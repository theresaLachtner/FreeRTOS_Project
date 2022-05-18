//task that polls for the current potentiometer value
static void TASK_getPotentiometerValue(void *pvParameters);
//task that polls for the current LDR value
static void TASK_getLDRValue(void *pvParameters);
//task that sets the PWM according to current LDR and PWM
static void TASK_setPWM(void *pvParameters);