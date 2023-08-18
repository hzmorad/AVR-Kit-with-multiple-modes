/*
 * PWM_1.c
 *
 * Created: 10/02/2018 10:18:02 ص
 *  Author: ahmed
 */ 

#include "PWM_1.h"

void PWM1_OCCR1B_init()
{
	SETBIT(TCCR1A,COM1B1);
	SETBIT(DDRD,4);
	SETBIT(TCCR1A,WGM10);
	SETBIT(TCCR1A,WGM11);
	SETBIT(TCCR1B,WGM12);
	SETBIT(TCCR1B,CS10);
//	OCR1B=550;//duty cycle=20%. cycle=2^10=1024
	
}

//duty= ocr1b/1023 *100
//100= ocr1b/1023 *100 ==> orc1b = 1023
//ocr1b= duty *10.23
void PWM1_OCCR1B_set_duty(uint8_t duty)
{
	
	OCR1B = duty * ((float)1023) / ((float)100);
}
