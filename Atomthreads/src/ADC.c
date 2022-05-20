#include "../lib/common.h"
#include "../lib/ADC.h"

// queue for sending current ADC channel to interrupt
extern ATOM_QUEUE _QUEUE_toInterrupt;
// queue for sending data ready bit to ADC read
extern ATOM_QUEUE _QUEUE_fromInterrupt;

//set voltage reference, prescaler and activate ADC
void ADC_init()
{
	//activate ADC
	ADCSRA = (1 << ADEN); 
	//set AVCC as voltage reference
	ADMUX = (1 << REFS0);
	//set the prescaler to 128 
	ADCSRA |= (1 << ADPS0)|(1 << ADPS1)|(1 << ADPS2);
}

//read single value from ADC-channel
uint16_t ADC_read(uint8_t channel)
{
	//clear channel register
	ADMUX &= ~(0x1F);
	//write channel to register
	ADMUX |= (channel & 0x1F);
	//start conversion
	ADCSRA |= (1 << ADSC);
	
	uint8_t msg;
	atomQueueGet(&_QUEUE_fromInterrupt, 10000, &msg);

	return ADCW;
}
