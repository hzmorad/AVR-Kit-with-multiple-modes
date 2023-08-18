/*
 * UART.h
 *
 * Created: 23/02/2018 01:54:48 م
 *  Author: ahmed
 */ 


#ifndef UART_H_
#define UART_H_

#include "std_macros.h"

void UART_init();
void UART_write(uint8_t data);
uint8_t UART_read();

#endif /* UART_H_ */