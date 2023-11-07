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
	
	printf("Interrupted. Count: %d\n", interruptCount);
	
	//msg_r = can_read();
	//printf("msg received ID:  %d\t", msg_r.id);
	//printf("msg received data: ");
	//for (int i = 0; i < 8; i++) {
		//printf("%d\t", msg_r.data[i]);
	//}
	
	//Clear interrupt flag?
	
	GIFR |= (1<<INTF0);
}