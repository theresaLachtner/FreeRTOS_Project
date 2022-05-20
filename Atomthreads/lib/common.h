#ifndef COMMON_H_
#define COMMON_H_

#define DEBUG

#include <avr/io.h>
#include <util/delay.h>

#include "../kernel/atom.h"
#include "../kernel/atomport-private.h"
#include "../kernel/atomtimer.h"
#include "../kernel/atommutex.h"
#include "../kernel/atomqueue.h"

// only included in debug-mode
#ifdef DEBUG
#include <stdio.h>
#include "debug.h"
#endif

// mutex for handling the ADC values
ATOM_MUTEX _MUTEX_ADC;
// queue for signaling a change in the ADC values to the PWM
ATOM_QUEUE _QUEUE_ADCchange;

// ADC channel of potentiometer
#define POT_CHANNEL 0
// ADC channel of light dependent resistor
#define LDR_CHANNEL 1

// upper voltage limit of the LDR
#define LDR_UPPER_LIMIT 4.2
// lower voltage limit of the LDR
#define LDR_LOWER_LIMIT 0.5

#define REGISTER_SIZE 256

#endif
