/*
 * motor.c
 *
 * Created: 07.11.2023 14:48:11
 *  Author: jonassfr
 */ 
#include "motor.h"
#include "sam.h"
#include "dac.h"
#include <stdio.h>
#include "delay.h"
#include "pid.h"
#include "can_interrupt.h"

int motor_init() {
	int err = 0;
	err = dac_init();
	if (err) {
		printf("ERROR: motor init failed");
		return -1;
	}
	
	//PMC->PMC_PCR = ID_PIOC;
	//PMC->PMC_PCR = ID_PIOD;
	
	PIOC->PIO_PER |= PIO_PC1 | PIO_PC2 | PIO_PC3 | PIO_PC4 | PIO_PC5 | PIO_PC7 | PIO_PC8;
	PIOC->PIO_ODR |= PIO_PC1 | PIO_PC2 | PIO_PC3 | PIO_PC4 | PIO_PC5 | PIO_PC7 | PIO_PC8;
	
 	PIOD->PIO_PER |= PIO_PD0 | PIO_PD1 | PIO_PD2 | PIO_PD9 | PIO_PD10;
	PIOD->PIO_OER |= PIO_PD0 | PIO_PD1 | PIO_PD2 | PIO_PD9 | PIO_PD10;
	PIOD->PIO_SODR = PIO_PD1;
	
    PMC->PMC_PCR = PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV_MCK | (ID_PIOC << PMC_PCR_PID_Pos);
    PMC->PMC_PCER0 |= 1 << (ID_PIOC);	
	
	return 0;
}

void motor_set_speed(uint16_t speed) {
	printf("motor speed set to %d \r", speed);
	dac_write(speed);
}

void motor_set_dir(uint8_t direction) {
	if (direction == 1) {
		PIOD->PIO_SODR = PIO_PD10; //Right
	}
	else if (direction == 0) {
		PIOD->PIO_CODR = PIO_PD10; //Left
	}
}

void motor_enable(uint8_t bool) {
	if (bool == 1) {
		PIOD->PIO_SODR = PIO_PD9; //Enable motor
	}
	else if (bool == 0) {
		PIOD->PIO_CODR = PIO_PD9; //Disable motor
	}
}

int motor_read_encoder() {
	PIOD->PIO_CODR = PIO_PD0; // STOP recording encoder values
	PIOD->PIO_CODR = PIO_PD2; // SELECT HIGH BYTE
	delay_ms(0.02);
	//PIOD->PIO_CODR = PIO_PD1; //reset encoder value
	//*data = (PIOC->PIO_PDSR & 0b11111111) << 8;
	uint8_t msb = (PIOC->PIO_PDSR & (0xFF << 1)) >> 1;
	//printf("ENCODER VALUE HIGH: %d \r", (int)PIOC->PIO_PDSR);
	PIOD->PIO_SODR = PIO_PD2; // SELECT LOW BYTE
	delay_ms(0.02);
	uint8_t lsb = (PIOC->PIO_PDSR & (0xFF << 1)) >> 1;
	//*data = *data + (PIOC->PIO_PDSR & 0b11111111);
	//printf(("ENCODER VALUE LOW: %d \r",PIOC->PIO_PDSR & 0b11111111)); 
	PIOD->PIO_CODR = PIO_PD1; //reset encoder value
	PIOD->PIO_SODR = PIO_PD1; 
	
	PIOD->PIO_SODR = PIO_PD0;
    uint16_t encoder_data = ((msb << 8) | lsb);
    if (encoder_data & (1 << 15)) {
	     //printf("ENCODER VALUE: %u\r",((uint16_t) (~encoder_data) + 1));
		 return ((uint16_t) (~encoder_data) + 1);
    }
	else {
	//printf("ENCODER VALUE: %d\r", (-encoder_data));
	}
	return -encoder_data;
    
}

	
	int scale_encoder_output(int value) {
		int scaled_val = value * 1400/250;
	}
	
	
	
	//eencoder - 0-1404
	//joystick - 0-256 midtpunkt 160

void motor_run(uint8_t dir) {
	printf("motor run called: value: %d\r", dir);
	uint8_t direction = 0;
	uint8_t enable = 0;
	if (dir > 200) {
		enable = 1;
		direction = 1;
	}
	else if (dir < 130) {
		enable = 1;
		direction = 0;
	}
	else {
		enable = 0;
	}
	motor_enable(enable);
	
	
	//read values from encoder and use it in a PID
	int encoder_output = motor_read_encoder();
	int current_pos = scale_encoder_output(encoder_output);
	float control_input = pid_regulator(message.data[2], current_pos);
	
	if(control_input > 0) {
		motor_set_dir(1);
		motor_set_speed(control_input);
		
	}
	else {
		motor_set_dir(0);
		motor_set_speed(-control_input);
	}
	
	
	motor_set_dir(direction);
	motor_set_speed(MOTOR_SPEED_5V);
	//delay_ms(50);
	//motor_enable(0);
	//delay_ms(10);
	//motor_enable(0);
	//motor_set_speed(MOTOR_SPEED_0V);
}




