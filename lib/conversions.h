//converts raw value from ADC to voltage
float Convert_toVoltage(uint16_t raw);
//adjust LDR to value between 0.0 and 5.0
void Adjust_LDR(float *ldr);
//convert voltage value to 8-bit integer for PWM regulation
uint8_t Convert_toPWM(float voltage, int16_t* pwm_val);