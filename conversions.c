#include "lib/common.h"
#include "lib/conversions.h"

//converts raw value from ADC to voltage
float Convert_toVoltage(uint16_t raw)
{
    float retVal = (float)raw * (5.0 / 1023.0);
    return retVal;
}

//adjust LDR to value between 0.0 and 5.0
void Adjust_LDR(float *ldr)
{
    *ldr -= LDR_LOWER_LIMIT;
    *ldr /= (LDR_UPPER_LIMIT - LDR_LOWER_LIMIT);
    *ldr *= 5.0;
    if (*ldr < 0)
    {
        *ldr = 0.0;
    }
    else if (*ldr > 5.0)
    {
        *ldr = 5.0;
    }
}

//convert voltage value to 8-bit integer for PWM regulation
uint8_t Convert_toPWM(float voltage, int16_t* pwm_val)
{
    //make sure, voltage value is within requested boundries - boundaries were checked for safety
    if(voltage >= -5.0 && voltage <= 5.0)
    {
        *pwm_val = (int16_t)((voltage / 5.0) * 255);
        return 0;
    }
    else
    {
        return 1;
    }
}