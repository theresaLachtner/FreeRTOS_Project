#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>


int main () {

	DDRD |= (1<<7);   // output at PD7, to connect an LED with current-limiting resistor

	PORTD |= (1<<4);  // momentry switch connects PD4 to GND, activate Pullup at PD4
	
	
	while (1) {    // endless loop!
		
		if ((PIND & (1<<4)) == 0)     {   // only if the switch is pressed 
			
			
			PORTD |= (1<<7);  // set bit 7 in register PORTD: switch on LED at PD 7
			_delay_ms(200);

			PORTD &= ~(1<<7);  // clear bit 7 in register PORTD: switch off LED at PD 7
			_delay_ms(200);
		}	
	}
}	
