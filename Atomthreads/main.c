#include "lib/common.h"
#include "lib/setup.h"
#include "lib/GPIO.h"
#include "lib/ADC.h"
#include "lib/threads.h"
#include <stdio.h>

// mutex for handling ADC values
extern ATOM_MUTEX _MUTEX_ADC;
// mutex for handling LDR value
extern ATOM_MUTEX _MUTEX_LDR;
// mutex for handling POT value
extern ATOM_MUTEX _MUTEX_POT;

// queue for signaling a change in the ADC values to the PWM
extern ATOM_QUEUE _QUEUE_ADCchange;
// queue storage
static uint8_t queueStorageADCchange[1];
// queue for sending data ready bit to ADC read
extern ATOM_QUEUE _QUEUE_fromInterrupt;
// queue storage
static uint8_t queueStorageFromInt[1];

// tcb storage for potentiometer thread
static ATOM_TCB potTCB;
// stack of the potentiometer thread
static uint8_t potSTACK[128];

// tcb storage for LDR thread
static ATOM_TCB ldrTCB;
// stack of the LDR thread
static uint8_t ldrSTACK[128];

// tcb storage for PWM thread
static ATOM_TCB pwmTCB;
// stack of the PWM thread
static uint8_t pwmSTACK[128];

// idle stack for atomOSInit function
static uint8_t idleThreadStack[128];

ISR(ADC_vect)
{
	// mandatory atomthreads function at the beginning of every ISR
	atomIntEnter();
	
	uint8_t msg = 1;
	// put go message to queue
	atomQueuePut(&_QUEUE_fromInterrupt, 10, &msg);

	// mandatory atomthreads function at the end of every ISR
	atomIntExit(TRUE);
}


int main () 
{
	//_delay_ms(5000);
	setup();

	if (atomOSInit(&idleThreadStack[0], 128, FALSE) == ATOM_OK)
	{
		UART_sendstring("atomOSInit succesful\n");
	}
	avrInitSystemTickTimer();

	if (atomThreadCreate(&potTCB, 10, THREAD_getPotentiometerValue, 0, &potSTACK[0], 128, TRUE) == ATOM_OK)
	{
		UART_sendstring("POT Task created\n");
	}
	if (atomThreadCreate(&ldrTCB, 10, THREAD_getLDRValue, 0, &ldrSTACK[0], 128, TRUE) == ATOM_OK)
	{
		UART_sendstring("LDR Task created\n");
	}
	if (atomThreadCreate(&pwmTCB, 20, THREAD_setPWM, 0, &pwmSTACK[0], 128, TRUE) == ATOM_OK)
	{
		UART_sendstring("PWM Task created\n");
	}
	// create the mutexes used for value handling
	atomMutexCreate(&_MUTEX_ADC);
	atomMutexCreate(&_MUTEX_LDR);
	atomMutexCreate(&_MUTEX_POT);
	// create the queues
	atomQueueCreate(&_QUEUE_ADCchange, &queueStorageADCchange[0], sizeof(uint8_t), 1);
	atomQueueCreate(&_QUEUE_fromInterrupt, &queueStorageFromInt[0], sizeof(uint8_t), 1);
	// start the sceduling process and run the threads
	atomOSStart();
}	
