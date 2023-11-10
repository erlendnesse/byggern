/*
 * adc.c
 *
 * Created: 12.09.2023 11:44:38
 *  Author: jonassfr
 */ 

#include "adc.h"
#include <avr/io.h>
#include <stdio.h>


void adc_init() {
	//All code in function inits pwm
	OCR3A = 0x02;
	DDRD |= (1 << PD4);
	TCCR3B |= (1 << WGM32); //Setting CTC
	TCCR3A |= (1 << COM3A0); //Clear OC3A on Compare Match, set OC3A at TOP. or toggle or smth.
	TCCR3B |= (1 << CS30);
	printf("-PWM init-\n");
}

uint8_t adc_read(uint8_t channel) {
	volatile uint8_t *ADC = (uint8_t*)0x1401;
	*ADC = 1;
	
	int ch0 = *ADC;
	int ch1 = *ADC;
	int ch2 = *ADC;
	int ch3 = *ADC;
	
	switch(channel) {
		case 0:
			return ch0;
		case 1:
			return ch1;
		case 2:
			return ch2;
		case 3:
			return ch3;
		default:
			printf("Channel not found, arg given: %d", channel);
			break;

	}
	return -1;
}


