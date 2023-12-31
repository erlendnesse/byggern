/*
 * CFile1.c
 *
 * Created: 19.09.2023 10:36:14
 *  Author: jonassfr
 */ 

#include "joystick.h"
#include "adc.h"
#include <avr/io.h>
#include "can.h"

void joystick_init(){
	DDRD |= (0 << PD5);
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

void joystick_transmit() {
	//Lese joystick posisjon og lagre til struct
	struct pos joy_pos = pos_read();
	
	//Oppretter structs iden can_write tar inn en struct
	struct Message pos_message = {.id = ID_POSITION, .length = 4};

	//Konverterer til uint8_t siden Message structen er definert for denne typen
	pos_message.data[0] = (uint8_t)adc_read(0); //joy_pos.x_pos;
	pos_message.data[1] = (uint8_t)adc_read(1); //joy_pos.y_pos;
	pos_message.data[2] = (uint8_t)adc_read(2); //right slider value
	uint8_t pd5_value = (PIND >> PIND5) & 1; //Read joystick button
	pos_message.data[3] = pd5_value;

	can_write(&pos_message);
	
}
