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

//struct menu_items menu(void);

void set_menu(){
	
}

void game_fsm() {
	volatile int menu_index = 1;
	oled_set_home();
	oled_set_position(menu_index, 100);
	oled_print_string("<-");
	volatile int direction = dir();
	while(1) {
		while(direction == NEUTRAL) {
			direction = dir();
			_delay_ms(750);
			//printf("Direction : %d\r\n", direction);
		}
		if (direction == UP && menu_index > 1) {
			printf("UP\r\n");
			oled_set_position(menu_index, 100);
			oled_print_string("  ");
			menu_index--;
			oled_set_position(menu_index, 100);
			oled_print_string("<-");
		}
		else if (direction == DOWN && menu_index < 7) {
			printf("DOWN\r\n");
			oled_set_position(menu_index, 100);
			oled_print_string("  ");
			menu_index++;
			oled_set_position(menu_index, 100);
			oled_print_string("<-");
		}
		printf("menu index %d\n\r", menu_index);
		direction = NEUTRAL;
	}
}
