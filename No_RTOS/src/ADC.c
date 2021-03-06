#include "../lib/common.h"
#include "../lib/ADC.h"

//set voltage reference, prescaler and activate ADC
void ADC_init()
{
	//activate ADC
	ADCSRA = (1 << ADEN); 
	//set AVCC as voltage reference
	ADMUX = (1 << REFS0);
	//set the prescaler to 128 
	ADCSRA |= (1 << ADPS0)|(1 << ADPS1)|(1 << ADPS2);
#ifdef DEBUG
	char debug_str[100];
	sprintf(debug_str, "%x", ADCSRA);
	UART_sendstring("ADCSRA: ");
	UART_sendstring(debug_str);
	UART_sendstring("\n");

	sprintf(debug_str, "%x", ADMUX);
	UART_sendstring("ADMUX: ");
	UART_sendstring(debug_str);
	UART_sendstring("\n");
#endif
}

//read single value from ADC-channel
uint16_t ADC_read(uint16_t channel)
{
	//clear channel register
	ADMUX &= ~(0x1F);
	//write channel to register
	ADMUX |= (channel & 0x1F);
	//start conversion
	ADCSRA |= (1 << ADSC);
	
//TODO - realize without polling
	
	//poll for completion
	while (ADCSRA & (1 << ADSC))
	{
		//wait
	}
	return ADCW;
	
//END TODO
}
