#include "lib/common.h"
#include "lib/setup.h"
#include "lib/GPIO.h"
#include "lib/ADC.h"
#include "lib/dimmer.h"
#include <stdio.h>

extern uint16_t _POT_value;
extern uint16_t _LDR_value;

int main () 
{
	//_delay_ms(5000);
	setup();
	
	while (LED_dim() == 0) 
	{
		
	}
}	
