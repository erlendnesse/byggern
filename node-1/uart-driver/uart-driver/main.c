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
#include "menu.h"

int main(void)
{
	// Set main sleep time
	//int sleep_time = 1000;
    //_delay_ms(sleep_time);
	
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
	game_fsm();
	// MAIN LOOP
    while (1) {
		printf("Direction : %d\r\n", dir());
		//_delay_ms(sleep_time);
		oled_set_home();
	}

	return 0;
}