/*
 * delay.c
 *
 * Created: 17.10.2023 11:28:32
 *  Author: erleness
 */ 
#include "delay.h"
#include "sam.h"


volatile float milliseconds = 0;

void SysTick_Handler(void) {
	milliseconds++;
}

void delay_ms(float ms) {
	float start_time = milliseconds;
	while ((milliseconds - start_time) < ms) {
		// You can add other tasks or code here; it won't block the delay
	}
}