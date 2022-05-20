#include "../lib/common.h"
#include "../lib/conversions.h"

// converts raw value from ADC to voltage
float Convert_toVoltage(uint16_t raw)
{
    float retVal = (float)raw * (5.0 / 1023.0);
    return retVal;
}

// adjust LDR to value between 0.0 and 5.0
void Adjust_LDR(uint16_t *ldr)
{
    *ldr -= 25;
    *ldr = (*ldr) * (255.0 / (214.0 - 25.0));
    if (*ldr < 0)
    {
        *ldr = 0;
    }
    else if (*ldr > 255)
    {
        *ldr = 255;
    }
}

// convert voltage value to 8-bit integer for PWM regulation
uint8_t Convert_toPWM(float voltage, int16_t *pwm_val)
{
    // make sure, voltage value is within requested boundries - boundaries were checked for safety
    if (voltage >= -5.0 && voltage <= 5.0)
    {
        *pwm_val = (int16_t)((voltage / 5.0) * 255);
        return 0;
    }
    else
    {
        return 1;
    }
}

// converts 10 bit ADC input to 8 bits to conform with PWM register size
void Convert_to8Bit(uint16_t *adc_val)
{
    *adc_val = (*adc_val) * (255.0 / 1023.0);
}