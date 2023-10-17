/*
 * CFile1.c
 *
 * Created: 26.09.2023 13:39:20
 *  Author: jonassfr
 */ 

#include "menu.h"
#include "oled.h"
#include "joystick.h"
#include <util/delay.h>
#include <avr/io.h>

//struct menu_items menu(void);

void set_menu(){
	
}

void game_fsm() {
	volatile int menu_index = 1;
	oled_set_home();
	oled_set_position(menu_index, 120);
	oled_print_string_large("<");
	volatile int direction = dir();
	while(1) {
		while(direction == NEUTRAL) {
			direction = dir();
			if (!(PIND & (1<<5) )) {
				printf("CLICKED Menu index: %d\r\n", menu_index);
			}
			_delay_ms(750);
		}
		if (direction == UP && menu_index > 1) {
			printf("UP\r\n");
			oled_set_position(menu_index, 120);
			oled_print_string_large(" ");
			menu_index--;
			oled_set_position(menu_index, 120);
			oled_print_string_large("<");
		}
		else if (direction == DOWN && menu_index < 7) {
			printf("DOWN\r\n");
			oled_set_position(menu_index, 120);
			oled_print_string_large(" ");
			menu_index++;
			oled_set_position(menu_index, 120);
			oled_print_string_large("<");
		}
		direction = NEUTRAL;
	}
}
