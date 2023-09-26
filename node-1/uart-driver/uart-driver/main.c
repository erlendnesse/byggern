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
#include "joystick.h"
#include "oled.h"

int main(void)
{
	// Set main sleep time
	int sleep_time = 1000;
    _delay_ms(sleep_time);
	
	// Initialize functions
	usart_init(MYUBRR);
	xmem_init();
	adc_init();
	joystick_init();
	oled_init();
	
	// Test SRAM functionality
	if (SRAM_test()) {
		printf("SRAM test failed\r\n");
		return 0;
	}
	
	// MAIN LOOP
	
	oled_set_position(1,1);
	oled_print_string("NIGERIA");
	
	


    while (1) {

	}

	return 0;
}