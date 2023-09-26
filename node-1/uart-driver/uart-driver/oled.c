/*
 * oled.c
 *
 * Created: 19.09.2023 18:34:36
 *  Author: jonassfr
 */ 


#include "oled.h"
#include "fonts.h"


void oled_init() {
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
	oled_reset();
}

void oled_reset() {
	for (int line = 0; line < 8; line++)
	{
		oled_goto_page(line);
		oled_goto_column(0);

		for (int i = 0; i < 128; i++)
		{
			write_data(0x00);
		}

	}
}

void oled_clear_page(int page) {
	oled_goto_page(page);
	for (int i = 0; i < 128; i++)
	{
		write_data(0x00);
	}
}

void oled_goto_column(int column) {
	if (0 <= column && column <= 127) {
		write_command(0x00 + (column&0x0F));
		write_command(0x10 + ((column&0xF0) >> 4));
	}
	
	 // Alternativ funksjon
	 //write_command(0x00 + (column % 16)); // Lower nibble
	 //write_command(0x10 + (column / 16)); // Higher nibble
}

void oled_goto_page(int page) {
	if (0 <= page && page <= 7) {
		write_command(0xB0 + page);
	}
}

void oled_set_position(int page, int column) {
	oled_goto_page(page);
	oled_goto_column(column);
}

void write_command(uint8_t command) {
	volatile uint8_t* address = (uint8_t*)0x1000;
	*address = command;
}

void write_data(uint8_t data) {
	volatile uint8_t* address = (uint8_t*)0x1200;
	*address = data;
}

void oled_print_char(char c) {
	if (' ' <= c && c <= '~') {
		for (int i = 0; i < 8; i++) {
			uint8_t character = pgm_read_byte(&(font8[c - 32][i]));
			write_data(character);
		}
	}
}

void oled_print_string(const char* string) {
	int i = 0;
	while (string[i] != '\0') {
		oled_print_char(string[i]);
		++i;
	}
}

void oled_set_home() {
	oled_set_position(0,1);
	oled_print_string("---MAIN MENU---");
	
	oled_set_position(7,1);
	oled_print_string("<< RETURN");
}
