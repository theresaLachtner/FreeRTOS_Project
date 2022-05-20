#include "../lib/common.h"
#include "../lib/dimmer.h"
#include "../lib/threads.h"

extern uint16_t _POT_value;
extern uint16_t _LDR_value;

// thread handles polling for the potentiometer value
void THREAD_getPotentiometerValue(uint32_t param)
{
    //activate interrupt for ADC ready interrupt
    ADCSRA |= (1 << ADIE);
    while (1)
    {
        LED_dim();
    }
}

// thread handles polling for the LDR value
void THREAD_getLDRValue(uint32_t param)
{
    
}

// thread adjusts PWM according to potentiometer and LDR
void THREAD_setPWM(uint32_t param)
{
    
}