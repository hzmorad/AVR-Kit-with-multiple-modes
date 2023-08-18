/*
 * UART.c
 *
 * Created: 23/02/2018 01:54:31 م
 *  Author: ahmed
 */ 
#include "UART.h"

void UART_init()
{
	// baud rate
	UBRRL=51;// baud rate 9600, F_CPU = 8Mhz
	/* enable receiver and transmitter */
	SETBIT(UCSRB,RXEN);
	SETBIT(UCSRB,TXEN);
	/* data=8 bit, no parity, one stop bit */
	SETBIT(UCSRC,URSEL);
	SETBIT(UCSRC,UCSZ0);
	SETBIT(UCSRC,UCSZ1);
	/* Enable Rx complete interrupt */
	SETBIT(UCSRB,RXCIE);
}
void UART_write(uint8_t data)
{	/* wait for empty transmit buffer */
	while(!READBIT(UCSRA,UDRE));
	UDR = data;
}
uint8_t UART_read()
{
	while(!READBIT(UCSRA,RXC));
	return UDR;
}