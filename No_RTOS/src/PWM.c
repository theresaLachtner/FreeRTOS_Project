#include "../lib/common.h"
#include "../lib/PWM.h"

extern uint16_t _POT_value;

void PWM_init()
{
    //glear OCA on compare match, set OC0A at BOTTOM
    TCCR0A |= (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);
    //prescaler of timer is 8
    TCCR0B |= (1 << CS01);
    OCR0A = 0x00;
}

void PWM_adjust(int16_t val)
{
    //add current OCR0A register to value
    val += OCR0A;
    //if sum is greater than maxium value of register, set register to 0xFF
    if (val > 0xFF)
    {
        OCR0A = 0xFF;
    }
    //if sum is smaller than mimimum value of register, set register to zero
    else if (val < 0x00)
    {
        OCR0A = 0x00;
    }
    //else, the adjusted value is valid and is written to register
    else
    {
        OCR0A = val;
    }
}