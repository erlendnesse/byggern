/*
 * uart-driver.c
 *
 * Created: 29.08.2023 15:05:08
 * Author : jonassfr
 */ 

#include "uart_driver.h"
#include <util/delay.h>

int main(void)
{
	int sleep_time = 1000;
    _delay_ms(sleep_time);
	usart_init(MYUBRR);
    while (1) 
    {
		//unsigned char test_char = usart_receive();
		//usart_transmit(test_char);
		_delay_ms(sleep_time);
		
		uart_printf("hello world");

    }
	return 0;
}

