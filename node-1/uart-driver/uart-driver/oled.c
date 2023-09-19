/*
 * oled.c
 *
 * Created: 19.09.2023 18:34:36
 *  Author: jonassfr
 */ 


#include "oled.h"

void write_command(uint8_t command) {
	volatile uint8_t* address = (uint8_t*)0x1000;
	*address = command;
}

void write_data(uint8_t data) {
	volatile uint8_t* address = (uint8_t*)0x1200;
	*address = data;
}

void oled_init()
{
	write_command(0xae); // display off
	write_command(0xa1); //segment remap
	write_command(0xda); //common pads hardware: alternative
	write_command(0x12);
	write_command(0xc8); //common output scan direction:com63~com0
	write_command(0xa8); //multiplex ration mode:63
	write_command(0x3f);
	write_command(0xd5); //display divide ratio/osc. freq. mode
	write_command(0x80);
	write_command(0x81); //contrast control
	write_command(0x50);
	write_command(0xd9); //set pre-charge period
	write_command(0x21);
	write_command(0x20); //Set Memory Addressing Mode
	write_command(0x02);
	write_command(0xdb); //VCOM deselect level mode
	write_command(0x30);
	write_command(0xad); //master configuration
	write_command(0x00);
	write_command(0xa4); //out follows RAM content
	write_command(0xa6); //set normal display
	write_command(0xaf); // display on
}