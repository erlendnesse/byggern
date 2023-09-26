/*
 * IncFile1.h
 *
 * Created: 26.09.2023 13:39:56
 *  Author: jonassfr
 */ 



#ifndef MENU_H_
#define MENU_H_

struct menu_items {
	char* menu_index1;
	char* menu_index2;
	char* menu_index3;
	char* menu_index4;
	char* menu_index5;
	char* menu_index6;
};

	
void set_menu();
void game_fsm();

#endif /* MENU_H_ */