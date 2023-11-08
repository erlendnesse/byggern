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
#include "motor.h"
#include "pid.h"
#include "solenoid.h"


int main(void)
{
	
	//Linjen under var fra den utdelte koden for node2 
    /* Initialize the SAM system */
    SystemInit();
	SysTick_Config(SystemCoreClock / 1000); //for the delay
	configure_uart();
	WDT->WDT_MR |= 1 << 15; //watchdog timer off
	uint32_t can_br =  0x00143156; //3 << 16 | 3 << 12 | 2 << 8 | 7 << 4 | 7;
	led_init();
	//timer_counter_init();
	PWM_init();
	motor_init();
	
	
	


	
	

	
	//uart_putchar('F');
    //uart_getchar(ch);
	//UART_Handler();
	//motor_run();
	can_init_def_tx_rx_mb(can_br);
	uint8_t i = 0;
	uint16_t encoder_value = 0;
   // MAIN LOOP
   float time_step = 1.0/50.0;
   
   //Init Pid with  k_p, k_i, k_d,  time_step,  max_control_input
	pid_init(1,0.1,1,time_step,1404);
   

   while (1) 
   {
		//motor_run();
	    //motor_set_speed(65535);
		toggle_led(i);
		//can_send(&msg, 0);
		//PWM->PWM_CH_NUM[5].PWM_CDTY = 780;
		delay_ms(20);
		
		//PIOD->PIO_CODR = PIO_PD0;
		
		//motor_read_encoder();
		
		//printf("joystick POS VALUE: %d\r\n", message.data[1]);
		
		//printf("node 2: slider POS VALUE: %d\r\n", message.data[2]);
		
		
		
		//printf("ENCODER VALUE: %d \r", encoder_value);
		
		//prev_value = message.data[0];
		//
		//if (prev_value == message.data[0]) {
			//motor_run(160);
		//}
		
		motor_run(message.data[2]);
		
			//printf("Current encoder position is:  %d\r\n", motor_read_encoder());
		
		
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
	PIOA->PIO_OER |=  PIO_PA19 | PIO_PA20;
}

