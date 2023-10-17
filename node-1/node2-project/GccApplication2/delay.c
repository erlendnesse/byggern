/*
 * delay.c
 *
 * Created: 17.10.2023 11:28:32
 *  Author: erleness
 */ 
#include "delay.h"
#include "sam.h"


volatile uint32_t milliseconds = 0;

void SysTick_Handler(void) {
	milliseconds++;
}

void delay_ms(uint32_t ms) {
	uint32_t start_time = milliseconds;
	while ((milliseconds - start_time) < ms) {
		// You can add other tasks or code here; it won't block the delay
	}
}