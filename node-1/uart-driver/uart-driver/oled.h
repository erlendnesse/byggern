/*
 * oled.h
 *
 * Created: 19.09.2023 18:34:26
 *  Author: jonassfr
 */ 


#ifndef OLED_H_
#define OLED_H_

#include <stdint.h>

void oled_goto_page(int page);
void oled_goto_column(int column);
void oled_set_position(int page, int column);

void write_command(uint8_t data);
void write_data(uint8_t data);

void oled_clear_page(int page);

void oled_reset();
void oled_split_string();
void oled_print_char(char c);
void oled_print_string(const char* string);





void oled_init();



#endif /* OLED_H_ */