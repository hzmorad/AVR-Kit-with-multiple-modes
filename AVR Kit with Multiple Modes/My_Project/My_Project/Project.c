/*
 * Project.c
 *
 * Created: 12/03/2018 11:42:56 ص
 *  Author: ahmed
 */ 
#include "Project.h"
uint8_t data=0;
uint8_t mode_num=0;
mode_A()
{
	//ADC_init();
//	ADC_Read(0);
	uint16_t ADC0=0;
	LCD_write_cmd(0x0c);
	LCD_write_string("Mode A");
	/*UART_write(mode_num);
	data=UART_read();*/
	while(data==1){
		/*UART_write(mode_num);
		data=UART_read();*/
	    ADC0=ADC_Read(0);//	ADC0=ADC0_Read();
		if(ADC0>900)
		{
			PWM1_OCCR1B_set_duty(90);
			PWM2_OCCR1A_set_duty(10);
		}
		else if(ADC0>600)
		{
			PWM1_OCCR1B_set_duty(60);
			PWM2_OCCR1A_set_duty(30);
		}
		else if(ADC0>300)
		{
			PWM1_OCCR1B_set_duty(40);
			PWM2_OCCR1A_set_duty(70);
		}
		else if(ADC0>100)
		{
			PWM1_OCCR1B_set_duty(20);
			PWM2_OCCR1A_set_duty(100);
		}
		else
		{
			PWM1_OCCR1B_set_duty(0);
			PWM2_OCCR1A_set_duty(0);
		}
	}
}

mode_B()
{
	PWM1_OCCR1B_set_duty(0);
	PWM2_OCCR1A_set_duty(0);
//	ADC1_init();
	uint16_t ADC1=0;
	LCD_write_cmd(0x0c);
	LCD_write_string("Mode B");
	/*UART_write(mode_num);
	data=UART_read();*/
	while(data==2){
		/*UART_write(mode_num);
		data=UART_read();*/
		ADC1=ADC_Read(1);//ADC1=ADC1_Read();
		if(ADC1>300)
		{
			SETBIT(PORTD,3);
		}
		else
		{
			CLRBIT(PORTD,3);
		}
	}
}

double store[100];//int32_t store[100];
char op[100];
uint8_t MathError_Flag;
uint8_t cursor_position;
uint8_t cursor_flag;
uint8_t cursor_shift;
mode_C()
{
	PWM1_OCCR1B_set_duty(0);
	PWM2_OCCR1A_set_duty(0);
	CLRBIT(PORTD,3);
	//UART_write(mode_num);
	//data=UART_read();*/
	LCD_write_string("Mode C");
	_delay_ms(500);
	cursor_flag=0;
	cursor_shift=0;
	LCD_write_cmd(0x01);
	LCD_write_cmd(0x80);
	LCD_write_cmd(0x0e);
	uint8_t now;
	uint8_t last;
	/*double store[100];//int32_t store[100];
	char op[100];*/
	uint8_t op_count=0;
	int32_t num=0;
	uint8_t count=0;
	uint8_t size_of_num=0;//
	cursor_position=1;
	MathError_Flag=0;
	uint8_t negative_Number_Flag=0;
	enum StageFlag{Enter_Number,Continue,Reset};//
	enum StageFlag my_Stage=Enter_Number;//Enter_First_Number;//
	while(data==3)
	{
		/*UART_write(mode_num);
		data=UART_read();*/
		now = keypad_read();
		if(now != last && now!=0)
		{
			if((now=='=')&&(my_Stage==Enter_Number)&&(size_of_num!=0))
			{
				while(cursor_shift>0)
				{
					LCD_write_cmd(0x1c);
					cursor_shift--;
				}
				while(negative_Number_Flag!=0)
				{
					num=num*-1;
					negative_Number_Flag--;
				}
				negative_Number_Flag=0;
				store[count]=num;
				LCD_write_cmd(0xc0);
				LCD_write_char('=');
				/*uint8_t i,j;
				int32_t result;
				int32_t get_float;*/
				store[count+1]='\0';
				op[op_count+1]='\0';
				if(MathError_Flag==0)
				{
					calculate();		
					my_Stage=Continue;//
				}
				else /*if(MathError_Flag==1)*/
				{
					LCD_write_string("Math Error");
					my_Stage=Reset;
				}				
			}
			else if((now>47)&&(now<58)&&(size_of_num<5)&&(my_Stage==Enter_Number))
			{
				LCD_write_char(now);num=(num*10)+(now-48);/*size_of_num++;*/cursor_position++;
				if(num==0){size_of_num=5;}else{size_of_num++;}
				if((op[op_count-1]=='/')&&(num==0)){MathError_Flag=1;}
				check_Cursor_Position();
			}
			else if((now=='+'||now=='-'||now=='*'||now=='/')&&(my_Stage==Enter_Number||my_Stage==Continue)&&(size_of_num!=0))
			{
				if(my_Stage!=Continue)
				{
					while(negative_Number_Flag!=0)
					{
						num=num*-1;
						negative_Number_Flag--;	
					}
					negative_Number_Flag=0;
					store[count]=num;
					num=0;
					count++;
					op[op_count]=now;
					op_count++;
				}
				else
				{
					count=1;
				    op_count=0;
				    op[op_count]=now;
					op_count++;
					num=0;
					LCD_write_cmd(0x1);
					LCD_write_cmd(0x80);
					LCD_write_string("Ans.");
					cursor_position=4;
				}
				LCD_write_char(now);
				my_Stage=Enter_Number;//
				size_of_num=0;//
				cursor_position++;
				check_Cursor_Position();
			}
			else if(now=='c')
			{
				LCD_write_cmd(0x1);
				LCD_write_cmd(0x80);
				num=0;
				count=0;
				my_Stage=Enter_Number;//
				size_of_num=0;//
				op_count=0;
				cursor_position=1;
				cursor_flag=0;
				MathError_Flag=0;
				negative_Number_Flag=0;
				check_Cursor_Position();
			}
			else if((now=='-')&&(my_Stage==Enter_Number)&&(size_of_num==0))
			{
				LCD_write_char(now);
				negative_Number_Flag++;
				cursor_position++;
				check_Cursor_Position();
			}
			else if((now=='+')&&(my_Stage==Enter_Number)&&(size_of_num==0))
			{
				LCD_write_char(now);
				cursor_position++;
				check_Cursor_Position();
			}
		}
		last=now;
	}
}

calculate()
{
	uint8_t i,j;
	int32_t result;
	int32_t get_float;
	for(i=0;store[i+1]!='\0';i++)
	{
		if(op[i]=='*')
		{
			store[i]=store[i]*store[i+1];
			for(j=i;store[j]!='\0';j++)
			{
				store[j+1]=store[j+2];
				op[j]=op[j+1];
			}
			i=-1;
		}
		else if(op[i]=='/')
		{
			/*if((uint8_t)store[i+1]==0)
			{
				MathError_Flag=1;
			}*/
			store[i]=store[i]/store[i+1];
			for(j=i;store[j]!='\0';j++)
			{
				store[j+1]=store[j+2];
				op[j]=op[j+1];
			}
			i=-1;
		}
	}
	for(i=0;store[i+1]!='\0';i++)
	{
		if(op[i]=='+')
		{
			store[i]=store[i]+store[i+1];
			for(j=i;store[j]!='\0';j++)
			{
				store[j+1]=store[j+2];
				op[j]=op[j+1];
			}
			i=-1;
		}
		else if(op[i]=='-')
		{
			store[i]=store[i]-store[i+1];
			for(j=i;store[j]!='\0';j++)
			{
				store[j+1]=store[j+2];
				op[j]=op[j+1];
			}
			i=-1;
		}
	}
	result=store[0];
	if((result>=2147483648)||(result<=-2147483648))
	{
		LCD_write_string("Out Of Range");
	}
	else if(result<0)
	{
		LCD_write_char('-');
		LCD_write_number(result*-1);
		LCD_write_char('.');
		get_float=(store[0]-((int32_t)store[0]))*100;
		LCD_write_number(get_float/10);
		LCD_write_number(get_float%10);
	}
	else if(result>=0)
	{
		LCD_write_number(result);
		LCD_write_char('.');
		get_float=(store[0]-((int32_t)store[0]))*100;
		LCD_write_number(get_float/10);
		LCD_write_number(get_float%10);
	}
}

check_Cursor_Position(){
	if(cursor_position>17)
	{
		if(cursor_position>40)
		{
			if(cursor_position>56&&cursor_flag==1)
			{
				cursor_flag=0;
			}
			if(cursor_flag==0)
			{
				LCD_write_cmd(0x80);
				cursor_flag=1;
				cursor_position=17;
			}
			/*LCD_write_cmd(0x80);*/
			/*for(int z=0;z<25;z++)
			{
				LCD_write_string(" ");
			}
			cursor_position=17;
			LCD_write_cmd(0x80);*/
		}
		LCD_write_cmd(0x18);
		cursor_shift++;
	}
}