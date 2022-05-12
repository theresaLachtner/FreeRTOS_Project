#include "lib/common.h"
#include "lib/setup.h"
#include "lib/GPIO.h"

int main () 
{
	setup();
	
	while (1) 
	{
			
		PORTD |= (1<<2);  // set bit 7 in register PORTD: switch on LED at PD 7
		_delay_ms(200);

		PORTD &= ~(1<<2);  // clear bit 7 in register PORTD: switch off LED at PD 7
		_delay_ms(200);	
	}
}	
