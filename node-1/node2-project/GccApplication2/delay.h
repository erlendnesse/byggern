/*
 * delay.h
 *
 * Created: 17.10.2023 11:28:18
 *  Author: erleness
 */ 


#ifndef DELAY_H_
#define DELAY_H_

#include <stdint.h>

void SysTick_Handler(void);

void delay_ms(float ms);


#endif /* DELAY_H_ */