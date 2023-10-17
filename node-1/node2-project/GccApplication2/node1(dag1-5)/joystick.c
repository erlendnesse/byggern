/*
 * CFile1.c
 *
 * Created: 19.09.2023 10:36:14
 *  Author: jonassfr
 */ 

#include "joystick.h"
#include "adc.h"
#include <avr/io.h>

void joystick_init(){
	PORTD |= (1 << PD5); //setup pullup for PD5 which is button input from Joystick
}

struct pos pos_read(void) {
	int g_f = 200/190; // gain factor to scale interval correctly
	int x_neutral = 160;
	int y_neutral = 162; // midpoint of interval
	
	struct pos position = {
		.x_pos = adc_read(0) * g_f - x_neutral, 
		.y_pos = adc_read(1) * g_f - y_neutral
	};

	if (position.x_pos > -5 && position.x_pos < 5) {
		position.x_pos = 0;
	}
	if (position.y_pos > -5 && position.y_pos < 5) {
		position.y_pos = 0;
	}
	if (position.x_pos <= -100) {
		position.x_pos = -100;
	}
	if (position.y_pos <= -100) {
		position.y_pos = -100;
	}
	if (position.x_pos >= 92) {
		position.x_pos = 100;
	}
	if (position.y_pos >= 92) {
		position.y_pos = 100;
	}
	
	return position;
}

dir_t dir() {
	struct pos position = pos_read();
	int x_input = position.x_pos;
	int y_input = position.y_pos;
	if (x_input < -50) {
		return LEFT;
	} 
	else if (x_input > 50) {
		return RIGHT;
	}
	if (y_input < -50) {
		return DOWN;
	}
	else if (y_input > 50) {
		return UP;
	}
	else if ((y_input > -50)&&(y_input <50)) {
		return NEUTRAL;
	}
	else if ((x_input > -50)&&(x_input <50)) {
		return NEUTRAL;
	}
	return NEUTRAL;
}