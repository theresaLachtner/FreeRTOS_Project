//set voltage reference, prescaler and activate ADC
void ADC_init();

//read single value from ADC-channel
uint16_t ADC_read(uint16_t channel);