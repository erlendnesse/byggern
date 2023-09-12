/*
 * adc.c
 *
 * Created: 12.09.2023 11:44:38
 *  Author: jonassfr
 */ 

#include "adc.h"
#include <avr/io.h>

	//TCCR3B |= (1 << WGM33);
	//TCCR3A |= (1 << WGM31);
	//TCCR3A |= (1 << WGM30);

void pwm_init() {
	OCR3A = 0x02;
	DDRD |= (1 << PD4);
	//TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS00);
	TCCR3B |= (1 << WGM32); //Setting CTC
	TCCR3A |= (1 << COM3A0); //Clear OC3A on Compare Match, set OC3A at TOP. or toggle or smth.
	TCCR3B |= (1 << CS30);
	printf("-PWM init-\n");
}

int adc_write_x() {
	volatile uint8_t *SRAM = (uint8_t*)0x1400;
	
	*SRAM = 0;
	
	return *SRAM;
}
int adc_write_y() {
	volatile uint8_t *SRAM = (uint8_t*)0x1401;
	
	*SRAM = 1;
	
	return *SRAM;
}

