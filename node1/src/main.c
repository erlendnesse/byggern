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
#include "can.h"
#include "interrupt.h"


int main(void)
{
	// Initialize functions
	usart_init(MYUBRR);
	xmem_init();
	adc_init();
	joystick_init();
	oled_init();
	interrupt_init();
	if (can_init()) {
		printf("Can init failed \r\n");
		return -1;
	}
	if (SRAM_test()) {
		printf("SRAM test failed\r\n");
		return -1;
	}
	game_fsm();
    while (1) {
		_delay_ms(130);
		joystick_transmit();
		if (game_finished) {
			return 0;
		}
	}
	return 0;
}