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

void interrupt_init() {
	DDRD |= (1 << PD2);
	
	MCUCR |= 1 << ISC01;
	GICR |= 1 << INT0;
	//SREG |= 1 << 7;
	
	sei();
}


// INT0 Interrupt Vector

ISR(INT0_vect) {
	printf("intterupted\r\n");
	
	//msg_r = can_read();
	//printf("msg received ID:  %d\t", msg_r.id);
	//printf("msg received data: ");
	//for (int i = 0; i < 8; i++) {
		//printf("%d\t", msg_r.data[i]);
	//}
}