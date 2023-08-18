/*
 * std_macros.h
 *
 * Created: 09/02/2018 10:37:51 ص
 *  Author: ahmed
 */ 

#ifndef STD_MACROS_H_
#define STD_MACROS_H_

#include <avr/io.h>
#define F_CPU 12000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

#define SETBIT(REG,BIT) (REG |= 1 << BIT)
#define CLRBIT(REG,BIT) (REG &= ~(1 << BIT))
#define TOGBIT(REG,BIT) (REG ^= 1 << BIT)
#define READBIT(REG,BIT) ((REG>>BIT) & 1)

#endif /* STD_MACROS_H_ */