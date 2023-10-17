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
#include "delay.h"
#include <stdio.h>

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
	
	
	

	CAN_MESSAGE msg = {
		.id = 14,
		.data_length = 3,
		.data = "node2"
	};
	

	
	//uart_putchar('F');
    //uart_getchar(ch);
	//UART_Handler();
	
	printf("main running");
	
   // MAIN LOOP
   while (1) {
	can_send(&msg, 0);
	delay_ms(1000);
	//can_receive(&msg_r, 5); 
   }

   return 0;
   
   
   
   
   
}
