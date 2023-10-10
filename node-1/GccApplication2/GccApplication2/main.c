/*
 * GccApplication2.c
 *
 * Created: 10.10.2023 11:14:07
 * Author : jonassfr
 */ 


#include "sam.h"
#include "uart.h"
#include "printf-stdarg.h"





int main(void)
{
	
	//Linjen under var fra den utdelte koden for node2 
    /* Initialize the SAM system */
    SystemInit();
	configure_uart();
	WDT->WDT_MR |= 1 << 15;
	

	//uint8_t * ch = ' ';
	//uart_putchar('F');
    //uart_getchar(ch);
	printf("nyy %c\r\n", 'B');
	//UART_Handler();
   // MAIN LOOP
   while (1) {
   }

   return 0;
   
   
   
   
   
}
