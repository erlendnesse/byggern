/*
 * delay.c
 *
 * Created: 17.10.2023 11:28:32
 *  Author: erleness
 */ 
#include "delay.h"
#include "sam.h"


volatile float sys_ticks = 0;

void SysTick_Handler(void) {
	sys_ticks++;
}

void delay_us(float us) { //tilsvares ish 1 mikrosekund, men ikke helt nøyaktig
	float start_time = sys_ticks;
	while ((sys_ticks - start_time) < us) {
	}
}