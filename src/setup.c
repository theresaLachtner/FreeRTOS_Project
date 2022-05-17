#include "../lib/setup.h"
#include "../lib/common.h"
#include "../lib/GPIO.h"
#include "../lib/ADC.h"
#include "../lib/PWM.h"

void setup()
{
#ifdef DEBUG
	UART_init(115200);
#endif
	//set GPIO ports D2-D4 to output for signal LEDs
	GPIO_setOutput(&DDRD, 2);
	GPIO_setOutput(&DDRD, 3);
	GPIO_setOutput(&DDRD, 4);
	GPIO_setOutput(&DDRD, 6);
	//set GPIO port B1 to output for brightness
	GPIO_setOutput(&DDRB, 1);
	//initialize ADC
	ADC_init();
	//initialize PWM
	PWM_init();
}
