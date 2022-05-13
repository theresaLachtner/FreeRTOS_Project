#include "lib/common.h"
#include "lib/ADC.h"
#include "lib/dimmer.h"
#include "lib/PWM.h"
#include "lib/conversions.h"

//ADC-converted value of potentiometer - global variable
extern uint16_t _POT_value;
//ADC-converted value of light dependant resistor - global variable
extern uint16_t _LDR_value;

//dim LED according to potentiometer and light dependant resistor values
uint8_t LED_dim()
{
    //initialize all variables
    int16_t pwm_val = 0;
    float pot_voltage = 0.0;
    float ldr_voltage = 0.0;
    //read current potentiometer value
    _POT_value = ADC_read(POT_CHANNEL);
    //read current LDR value
    _LDR_value = ADC_read(LDR_CHANNEL);
    //convert raw ADC values to voltage
    pot_voltage = Convert_toVoltage(_POT_value);
    ldr_voltage = Convert_toVoltage(_LDR_value);
    Adjust_LDR(&ldr_voltage);

    if(Convert_toPWM((pot_voltage - ldr_voltage), &pwm_val) == 0)
    {
        PWM_adjust(pwm_val);
    }

    return 0;
}