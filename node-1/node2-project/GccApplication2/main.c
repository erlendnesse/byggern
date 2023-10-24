/*
 * GccApplication2.c
 *
 * Created: 10.10.2023 11:14:07
 * Author : jonassfr
 */ 


#include "sam.h"
#include "uart.h"
#include "printf-stdarg.h"
#include "can_controller.h"
#include "can_interrupt.h"
#include "delay.h"
#include "timer_counter.h"
#include "pwm_servo.h"
#include <stdio.h>
#include <stdint.h>


int main(void)
{
	
	//Linjen under var fra den utdelte koden for node2 
    /* Initialize the SAM system */
    SystemInit();
	SysTick_Config(SystemCoreClock / 1000); //for the delay
	configure_uart();
	WDT->WDT_MR |= 1 << 15; //watchdog timer off
	uint32_t can_br =  0x00143156; //3 << 16 | 3 << 12 | 2 << 8 | 7 << 4 | 7;
		
	can_init_def_tx_rx_mb(can_br);
	led_init();
	//timer_counter_init();
	PWM_init();

	

	CAN_MESSAGE msg = {
		.id = 14,
		.data_length = 3,
		.data = "node2"
	};
	

	
	//uart_putchar('F');
    //uart_getchar(ch);
	//UART_Handler();
	


	uint8_t i = 0;
   // MAIN LOOP
   while (1) {
	toggle_led(i);
	//can_send(&msg, 0);
	//PWM->PWM_CH_NUM[5].PWM_CDTY = 780;
	delay_ms(1000);
	//can_receive(&msg_r, 5); 
	i++;
	}
   return 0;
}


void toggle_led(uint8_t count) {
	if (count % 2) {
		PIOA->PIO_CODR = PIO_PA19 ;
		PIOA->PIO_SODR |=  PIO_PA20;
	}
	else
	{
		PIOA->PIO_CODR = PIO_PA20;
		PIOA->PIO_SODR |=  PIO_PA19;
	}
}

void led_init() {
	PMC->PMC_PCR = 1 << 12;
	PIOA->PIO_OER |=  PIO_PA19 | PIO_PA20;
	
}