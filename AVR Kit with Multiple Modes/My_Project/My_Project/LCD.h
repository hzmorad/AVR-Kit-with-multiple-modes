/*
 * LCD.h
 *
 * Created: 16/02/2018 11:57:36 ص
 *  Author: ahmed
 */ 


#ifndef LCD_H_
#define LCD_H_
#include "std_macros.h"

#define D7(x) (x==1)?SETBIT(PORTA,7):CLRBIT(PORTA,7); //#define D7(x) if(x==1) SETBIT(PORTA,7);else CLRBIT(PORTA,7);
#define D6(x) (x==1)?SETBIT(PORTA,6):CLRBIT(PORTA,6);
#define D5(x) (x==1)?SETBIT(PORTA,5):CLRBIT(PORTA,5);
#define D4(x) (x==1)?SETBIT(PORTA,4):CLRBIT(PORTA,4);
#define EN(x) (x==1)?SETBIT(PORTB,3):CLRBIT(PORTB,3);
#define RS(x) (x==1)?SETBIT(PORTB,1):CLRBIT(PORTB,1);
#define RW(x) (x==1)?SETBIT(PORTB,2):CLRBIT(PORTB,2);

void LCD_init();
void LCD_write_cmd(uint8_t cmd);
void LCD_write_char(uint8_t data);
void LCD_write_string(uint8_t* data);
void LCD_write_number(uint32_t num);

#endif /* LCD_H_ */