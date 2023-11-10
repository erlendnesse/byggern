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
	//Used some of the same numbers on Time quantas as other groups:
	uint32_t can_br =  0x00143156; //3 << 16 | 3 << 12 | 2 << 8 | 7 << 4 | 7; Time quantas 
	led_init();
	PWM_init();
	motor_init();
	solenoid_init();

	can_init_def_tx_rx_mb(can_br);
	uint8_t i = 0;
   float time_step = 1.0/40.0;
   
   //Init Pid with  k_p, k_d,  time_step,  max_control_input
   // no dampning used, only PI
	pid_init(0.1,0.01, 0.0,time_step,1404);

   while (1) 
   {
		toggle_led(i);
		delay_us(10);
		motor_run(message.data[2]);	//slider pos
		if (!(i % 3)){
			if(!message.data[3]) {
				printf("button_pressed\r");
				solenoid_shoot(1);
			}
		}
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

