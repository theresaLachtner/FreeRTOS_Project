#ifndef COMMON_H_
#define COMMON_H_

#define DEBUG

#include <avr/io.h>
#include <util/delay.h>

//only included in debug-mode
#ifdef DEBUG
#include <stdio.h>
#include "debug.h"
#endif

//ADC-converted value of potentiometer
uint16_t _POT_value;
//ADC-converted value of light dependant resistor
uint16_t _LDR_value;

//ADC channel of potentiometer
#define POT_CHANNEL 0
//ADC channel of light dependent resistor
#define LDR_CHANNEL 1

//upper voltage limit of the LDR
#define LDR_UPPER_LIMIT 4.2
//lower voltage limit of the LDR
#define LDR_LOWER_LIMIT 0.5

#define REGISTER_SIZE 256

#endif
