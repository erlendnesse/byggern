/*
 * uart-driver.c
 *
 * Created: 29.08.2023 15:05:08
 * Author : jonassfr
 */ 

#include "uart_driver.h"
#include <util/delay.h>
#include "xmem.h"
#include <avr/io.h>



int main(void)
{
	int sleep_time = 1000;
    _delay_ms(sleep_time);
	usart_init(MYUBRR);
	

	xmem_init();

	//DDRA = 0;

	SRAM_test();
	
    while (1) 
    {
		//unsigned char test_char = usart_receive();
		//usart_transmit(test_char);
		_delay_ms(sleep_time*2);
		//xmem_write();
		
		//tes
		
		

		//PORTA ^= 1;
		//printf("hello world\n, number: %d", 10);
    }
	return 0;
}

