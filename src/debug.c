#include "../lib/common.h"
#include "../lib/debug.h"

//initialize UART
void UART_init(uint32_t baudrate)
{
    //formula for baudrate register, double speed mode
    uint16_t value = (F_CPU / 8 / baudrate) -1;  

    //use only higher 8 bits of value for UBRR0H (high byte)
    UBRR0H = (uint8_t)(value >> 8);  
    //use only lower 8 bits of value for UBRRL (low byte) 
    UBRR0L = (uint8_t)(value & 0xff); 

    //set bit for double speed mode selection in register UCSR0A
    UCSR0A |= (1<<U2X0);  
    //activate UART transmit and receive
    UCSR0B |= (1<<RXEN0) + (1<<TXEN0);  

}

//transmit single byte via UART
void UART_transmit(uint8_t byte_to_send) 
{

   //wait until UART data register is free to accept a new byte  
    while ((UCSR0A & (1<<UDRE0)) == 0)
    {
        //wait
    }
    //transmit the byte   
    UDR0 = byte_to_send;   

}

//transmit string via UART
void UART_sendstring(char *p) 
{
    while (*p) 
    {
        UART_transmit (*p);
        p++;
    }
}