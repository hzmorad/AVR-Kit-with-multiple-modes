/*
 * My_Project.c
 *
 * Created: 28/02/2018 02:12:47 م
 *  Author: ahmed
 */ 

#include "Project.h"

//uint8_t mode_num=0;

int main(void)
{
//	SETBIT(DDRD,7);
	SETBIT(DDRD,3);
	SETBIT(MCUCR,ISC00);
	SETBIT(MCUCR,ISC01);
	SETBIT(GICR,INT0);
	SETBIT(SREG,7);
	LCD_init();
	UART_init();
	PWM1_OCCR1B_init();
	PWM2_OCCR1A_init();
	keypad_init();
	ADC_init();

	while(1)
	{	

//		UART_write(mode_num);
//		data=UART_read();
		switch(data)
		{
			case 1:
			 mode_A();
			 break;
			case 2:
			 mode_B();
			 break;
			case 3:
			 mode_C();
			 break;
		}
		LCD_write_cmd(0x1);
		LCD_write_cmd(0x80);	
	}
}

ISR(INT0_vect)
{
//	TOGBIT(PORTD,7);
	mode_num = (mode_num>2) ? 1:mode_num+1;
//	_delay_ms(1);
	UART_write(mode_num);
//	data=UDR;
//	data=UART_read();
//	data=mode_num;
}
ISR(USART_RXC_vect)
{
	data=UDR;
}