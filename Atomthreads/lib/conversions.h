// converts raw value from ADC to voltage
float Convert_toVoltage(uint16_t raw);
// adjust LDR to value between 0.0 and 5.0
void Adjust_LDR(uint16_t *ldr);
// convert voltage value to 8-bit integer for PWM regulation
uint8_t Convert_toPWM(float voltage, int16_t *pwm_val);
// converts 10 bit ADC input to 8 bits to conform with PWM register size
void Convert_to8Bit(uint16_t *adc_val);