/*
 * PWM_1.h
 *
 * Created: 10/02/2018 10:18:18 ص
 *  Author: ahmed
 */ 


#ifndef PWM_1_H_
#define PWM_1_H_

#include "std_macros.h"

void PWM1_OCCR1B_init();
void PWM1_OCCR1B_set_duty(uint8_t duty);

#endif /* PWM_1_H_ */