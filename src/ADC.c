#include "../lib/common.h"
#include "../lib/ADC.h"

// handle for the channel info queue
extern QueueHandle_t _QH_ADCready;

//set voltage reference, prescaler and activate ADC
void ADC_init()
{
	//activate ADC + interrupt
	ADCSRA = (1 << ADEN) | (1 << ADIE); 
	//set AVCC as voltage reference
	ADMUX = (1 << REFS0);
	//set the prescaler to 128 
	ADCSRA |= (1 << ADPS0)|(1 << ADPS1)|(1 << ADPS2);
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
	
	// send current channel to queue
	QueueMessage_t channelInfo = 0;
	xQueueReceive(_QH_ADCready, &channelInfo, (TickType_t)10000);

	//return the raw converted value
	return ADCW;
}
