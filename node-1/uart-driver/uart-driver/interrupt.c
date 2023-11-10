/*
 * interrupt.c
 *
 * Created: 17.10.2023 13:37:50
 *  Author: erleness
 */ 


#include "interrupt.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>
#include "oled.h"

volatile int game_finished = 0;
volatile int interruptCount = 0;

void interrupt_init() {
	printf("-Interrupt init-\n\r");
	DDRD |= (0 << PD2);

	MCUCR |= 1 << ISC01;
	GICR |= 1 << INT0;
	//SREG |= 1 << 7;
	
	sei();
}



// INT0 Interrupt Vector

ISR(INT0_vect) {
	interruptCount++;
	_delay_ms(1000);
	
	printf("Interrupted. Count: %d\n\r", interruptCount);
	
	oled_set_position(4,90);
	oled_print_string_large("  ");
	
	switch(interruptCount) {
		case 1:
			oled_print_string_large("1");
			break;
		case 2:
			oled_print_string_large("2");
			break;
		case 3:
			oled_print_string_large("3");
			break;
		case 4:
			oled_print_string_large("4");
			break;
		case 5:
			oled_print_string_large("5");
			break;
		case 6:
			oled_print_string_large("6");
			break;
		case 7:
			oled_print_string_large("7");
			break;
		case 8:
			oled_print_string_large("8");
			break;
		case 9:
			oled_print_string_large("9");
			break;
		case 10:
			oled_print_string_large("10");
			break;
		case 11:
			oled_print_string_large("11");
			break;
		case 12:
			oled_print_string_large("12");
			break;
		case 13:
			oled_print_string_large("13");
			break;
		case 14:
			oled_print_string_large("14");
			break;
		case 15:
			oled_print_string_large("15");
			break;
		case 16:
			oled_print_string_large("16");
			break;
		case 17:
			oled_print_string_large("17");
			break;
		case 18:
			oled_print_string_large("18");
			break;
		case 19:
			oled_print_string_large("19");
			break;
		case 20:
			oled_print_string_large("20");
			oled_set_position(1,0);
			oled_print_string_large("---YOU LOST---");
			game_finished = 1;
			break;
		default:
			game_finished = 1;
			break;
	}	
	GIFR |= (1<<INTF0);
}