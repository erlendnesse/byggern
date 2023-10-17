/*
 * uart_driver.c
 *
 * Created: 29.08.2023 15:05:56
 *  Author: jonassfr
 */ 

#include <avr/io.h>
#include "uart_driver.h"

void usart_init(uint8_t ubrr) {
	/* Set baud rate */
	UBRR0H = (uint8_t)(ubrr>>8);
	UBRR0L = (uint8_t)ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 1stop bit */
	UCSR0C = (1<<URSEL0)|(3<<UCSZ00);
	fdevopen(usart_transmit, usart_receive);
}




void usart_transmit(uint8_t data) {
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) ) {	
	}
	
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

uint8_t usart_receive(void) {
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) ) {
	}
	/* Get and return received data from buffer */
	return UDR0;
}

void usart_flush(void) {
	uint8_t dummy;
	while ( UCSR0A & (1<<RXC0) ) {
		dummy = UDR0;
	}
}

