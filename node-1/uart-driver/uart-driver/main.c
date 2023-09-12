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
#include "adc.h"



int main(void)
{
	int sleep_time = 1000;
    _delay_ms(sleep_time);
	usart_init(MYUBRR);
	

	xmem_init();
	pwm_init();
	//SRAM_test();
	



    while (1) 
    {
		//unsigned char test_char = usart_receive();
		//usart_transmit(test_char);
		_delay_ms(sleep_time*0);
		
		//test av chipselect på ADC. Setter PD5 høy, sender dette inn på 
		volatile uint8_t *SRAM = (uint8_t*)0x1401;
			
		*SRAM = 1;
		printf("ADC value: %d\n\r", *SRAM);
		

		//PORTA ^= 1;
		
    }
	return 0;
}

