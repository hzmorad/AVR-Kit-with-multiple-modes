/*
 * Keypad.c
 *
 * Created: 17/02/2018 12:58:24 م
 *  Author: ahmed
 */ 

#include "Keypad.h"

/*
uint8_t keypad_matrix[] = {
 '7','4','1','c',
 '8','5','2','0',
 '9','6','3','=',
 '/','*','-','+',
};*/
uint8_t keypad_matrix[] = {
 '/','*','-','+',
 '=','9','6','3',
 '0','8','5','2',
 'c','7','4','1',
};
/*
uint8_t keypad_matrix[] = {
	'/','=','0','c',
	'*','9','8','7',
	'-','6','5','4',
	'+','3','2','1',
};*/
void keypad_init()
{
	CLRBIT(DDRC,0);CLRBIT(DDRC,1);CLRBIT(DDRC,2);CLRBIT(DDRC,3);
	SETBIT(PORTC,0);SETBIT(PORTC,1);SETBIT(PORTC,2);SETBIT(PORTC,3);
	SETBIT(DDRC,4);SETBIT(DDRC,5);SETBIT(DDRC,6);SETBIT(DDRC,7);
}
uint8_t keypad_read()
{
	CLRBIT(PORTC,4);SETBIT(PORTC,5);SETBIT(PORTC,6);SETBIT(PORTC,7);
	_delay_ms(1);
	if(!READBIT(PINC,0)) return keypad_matrix[0];
	if(!READBIT(PINC,1)) return keypad_matrix[1];
	if(!READBIT(PINC,2)) return keypad_matrix[2];
	if(!READBIT(PINC,3)) return keypad_matrix[3];
	
	SETBIT(PORTC,4);CLRBIT(PORTC,5);SETBIT(PORTC,6);SETBIT(PORTC,7);
	_delay_ms(1);
	if(!READBIT(PINC,0)) return keypad_matrix[4];
	if(!READBIT(PINC,1)) return keypad_matrix[5];
	if(!READBIT(PINC,2)) return keypad_matrix[6];
	if(!READBIT(PINC,3)) return keypad_matrix[7];
	
	SETBIT(PORTC,4);SETBIT(PORTC,5);CLRBIT(PORTC,6);SETBIT(PORTC,7);
	_delay_ms(1);
	if(!READBIT(PINC,0)) return keypad_matrix[8];
	if(!READBIT(PINC,1)) return keypad_matrix[9];
	if(!READBIT(PINC,2)) return keypad_matrix[10];
	if(!READBIT(PINC,3)) return keypad_matrix[11];
	
	SETBIT(PORTC,4);SETBIT(PORTC,5);SETBIT(PORTC,6);CLRBIT(PORTC,7);
	_delay_ms(1);
	if(!READBIT(PINC,0)) return keypad_matrix[12];
	if(!READBIT(PINC,1)) return keypad_matrix[13];
	if(!READBIT(PINC,2)) return keypad_matrix[14];
	if(!READBIT(PINC,3)) return keypad_matrix[15];
	return 0;
}