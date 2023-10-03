/*
 * uart-driver.c
 *
 * Created: 29.08.2023 15:05:08
 * Author : jonassfr
 */ 

#include "uart_driver.h"
#include <util/delay.h>
#include <stdio.h>
#include "xmem.h"
#include <avr/io.h>
#include "adc.h"
#include "joystick.h"
#include "oled.h"
#include "menu.h"
#include "spi.h"
#include "mcp.h"
#include "sram_test.h"


int main(void)
{
	// Set main sleep time
    //_delay_ms(sleep_time);
	
	// Initialize functions
	usart_init(MYUBRR);
	xmem_init();
	adc_init();
	joystick_init();
	oled_init();
	if (mcp2515_init()) {
		printf("mcp2515 init failed \r\n");
		return -1;
	}
	
	// Test SRAM functionality
	if (SRAM_test()) {
		printf("SRAM test failed\r\n");
		return -1;
	}
	
	mcp2515_mode_select(MODE_LOOPBACK);
	//game_fsm();
	// MAIN LOOP
    while (1) {
		mcp2515_print("ABC");
		_delay_ms(6000);
		//mcp2515_reception(0x11, 2);
		_delay_ms(1000);
	}

	return 0;
}