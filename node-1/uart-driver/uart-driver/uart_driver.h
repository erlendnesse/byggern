/*
 * uart_driver.h
 *
 * Created: 29.08.2023 15:08:45
 *  Author: jonassfr
 */ 


#ifndef UART_DRIVER_H_
#define UART_DRIVER_H_

#define FOSC 4915200// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

#include <stdint.h>


void usart_init(uint8_t ubrr);

void usart_transmit(unsigned char data);

unsigned char usart_receive(void);

void usart_flush(void);

void uart_printf(void);

#endif /* UART_DRIVER_H_ */