/*
 * oled.h
 *
 * Created: 19.09.2023 18:34:26
 *  Author: jonassfr
 */ 

#include <stdint.h>

#ifndef OLED_H_
#define OLED_H_

void oled_init();
void write_command(uint8_t data);
void write_data(uint8_t data);



#endif /* OLED_H_ */