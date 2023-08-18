/*
 * LCD.c
 *
 * Created: 16/02/2018 11:57:20 ص
 *  Author: ahmed
 */ 
#include "LCD.h"

void LCD_init()
{
	SETBIT(DDRA,4);SETBIT(DDRA,5);SETBIT(DDRA,6);SETBIT(DDRA,7);
	SETBIT(DDRB,1);SETBIT(DDRB,2);SETBIT(DDRB,3);
	RW(0);
	LCD_write_cmd(0x2);
	LCD_write_cmd(0x28);
	LCD_write_cmd(0x01);
	LCD_write_cmd(0x0c);
	LCD_write_cmd(0x06);
	LCD_write_cmd(0x80);
	_delay_ms(20);
}
void LCD_write_cmd(uint8_t cmd)
{
	RS(0);
	D7(READBIT(cmd,7));
	D6(READBIT(cmd,6));
	D5(READBIT(cmd,5));
	D4(READBIT(cmd,4));
	EN(1);_delay_ms(1);
	EN(0);_delay_ms(1);
	D7(READBIT(cmd,3));
	D6(READBIT(cmd,2));
	D5(READBIT(cmd,1));
	D4(READBIT(cmd,0));
	EN(1);_delay_ms(1);
	EN(0);_delay_ms(1);
}
void LCD_write_char(uint8_t data)
{
	RS(1);
	D7(READBIT(data,7));
	D6(READBIT(data,6));
	D5(READBIT(data,5));
	D4(READBIT(data,4));
	EN(1);_delay_ms(1);
	EN(0);_delay_ms(1);
	D7(READBIT(data,3));
	D6(READBIT(data,2));
	D5(READBIT(data,1));
	D4(READBIT(data,0));
	EN(1);_delay_ms(1);
	EN(0);_delay_ms(1);
}
void LCD_write_string(uint8_t* data)
{
	uint8_t i=0;
	for(i=0;data[i]!='\0';i++)
	{
		LCD_write_char(data[i]);
	}
}
void LCD_write_number(uint32_t num)
{
	uint32_t i=num,factor=1;
	uint8_t flag=1,digits=1;
	if(num<10)
	{
		LCD_write_char(num+48);
	}
	else
	{
		while(i>=10)
		{
			i/=10;
			factor*=10;
			digits++;	
		}
		while(digits--)
		{
			if(flag==1)
			{
				LCD_write_char((num/factor)+48);
				flag=0;
			}
			else
			{
				factor/=10;
				LCD_write_char(((num/factor)%10)+48);
			}
		}
	}
}
/*
void LCD_write_number(uint32_t num)
{
	if(num < 10)
	{
		LCD_write_char(num+48);
	}
	else if(num < 100)
	{
		LCD_write_char(num/10+48);
		LCD_write_char(num%10+48);
	}
	else if(num < 1000)//987
	{
		LCD_write_char(num/100+48);
		LCD_write_char((num/10)%10+48);
		LCD_write_char(num%10+48);
	}
	else if(num < 10000)//9876
	{
		LCD_write_char(num/1000+48);
		LCD_write_char((num/100)%10+48);
		LCD_write_char((num/10)%10+48);
		LCD_write_char(num%10+48);
	}
	else if(num < 100000)//98765
	{
		LCD_write_char(num/10000+48);
		LCD_write_char((num/1000)%10+48);
		LCD_write_char((num/100)%10+48);
		LCD_write_char((num/10)%10+48);
		LCD_write_char(num%10+48);
	}
	else if(num < 1000000)//987654
	{
		LCD_write_char(num/100000+48);
		LCD_write_char((num/10000)%10+48);
		LCD_write_char((num/1000)%10+48);
		LCD_write_char((num/100)%10+48);
		LCD_write_char((num/10)%10+48);
		LCD_write_char(num%10+48);
	}
	else if(num < 10000000)//9876543
	{
		LCD_write_char(num/1000000+48);
		LCD_write_char((num/100000)%10+48);
		LCD_write_char((num/10000)%10+48);
		LCD_write_char((num/1000)%10+48);
		LCD_write_char((num/100)%10+48);
		LCD_write_char((num/10)%10+48);
		LCD_write_char(num%10+48);
	}
	else if(num < 100000000)//98765432
	{
		LCD_write_char(num/10000000+48);
		LCD_write_char((num/1000000)%10+48);
		LCD_write_char((num/100000)%10+48);
		LCD_write_char((num/10000)%10+48);
		LCD_write_char((num/1000)%10+48);
		LCD_write_char((num/100)%10+48);
		LCD_write_char((num/10)%10+48);
		LCD_write_char(num%10+48);
	}
	else if(num < 1000000000)//987654321
	{
		LCD_write_char(num/100000000+48);
		LCD_write_char((num/10000000)%10+48);
		LCD_write_char((num/1000000)%10+48);
		LCD_write_char((num/100000)%10+48);
		LCD_write_char((num/10000)%10+48);
		LCD_write_char((num/1000)%10+48);
		LCD_write_char((num/100)%10+48);
		LCD_write_char((num/10)%10+48);
		LCD_write_char(num%10+48);
	}
}*/