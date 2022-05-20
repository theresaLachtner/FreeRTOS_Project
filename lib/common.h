#ifndef COMMON_H_
#define COMMON_H_

#define DEBUG

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "../FreeRTOS-Kernel/include/FreeRTOS.h"
#include "../FreeRTOS-Kernel/include/task.h"
#include "../FreeRTOS-Kernel/include/semphr.h"
#include "../FreeRTOS-Kernel/include/queue.h"

// only included in debug-mode
#ifdef DEBUG
#include <stdio.h>
#include "debug.h"
#endif

//------------------------------------------------------------------------
// GLOBAL VARIABLE DECLARATION
//------------------------------------------------------------------------

// task handle for get potentiometer value
TaskHandle_t _TH_getPOTval;
// task handle for get LDR value
TaskHandle_t _TH_getLDRval;
// handle for the pwm task
TaskHandle_t _TH_setPWM;

// handle for the ADC mutex semaphore
xSemaphoreHandle _MUTEX_ADC;
// handle for the POT value
xSemaphoreHandle _MUTEX_POT;
// handle for the LDR value
xSemaphoreHandle _MUTEX_LDR;

// handle for the channel info queue
QueueHandle_t _QH_ADCready;

//------------------------------------------------------------------------
// PRIVATE TYPEDEF
//------------------------------------------------------------------------

typedef uint16_t QueueMessage_t;

//------------------------------------------------------------------------
// PRIVATE MAKROS
//------------------------------------------------------------------------

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
