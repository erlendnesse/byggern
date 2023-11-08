/*
 * PWM.c
 *
 * Created: 24.10.2023 08:42:28
 *  Author: adriatom
 */

#include "pwm_servo.h"
#include "can_controller.h"
#include <stdio.h>

#define max_duty_cycle_value 180
#define min_duty_cycle_value 80
#define mean_duty_cycle_value 127

void PWM_init(void){
	printf("PWM init...\r");
	PMC->PMC_PCER1 |= PMC_PCER1_PID36;// Peripheral Clock Enable PWM
	PIOC->PIO_PDR |= PIO_PDR_P19;// Disable Register
	PIOC->PIO_ABSR |= PIO_ABSR_P19;// Peripheral Select

	PMC->PMC_PCR |= PMC_PCR_EN;
	/* PWM Clock Register*/
	PWM->PWM_CLK |= 1 << PWM_CLK_DIVA_Pos;
	PWM->PWM_SCM |= PWM_SCM_UPDM_MODE0;

	PWM->PWM_CH_NUM[5].PWM_CMR = PWM_CMR_CPRE_MCK_DIV_1024 | PWM_CMR_CPOL;
	PWM->PWM_CH_NUM[5].PWM_CPRD = 1641;
	PWM->PWM_CH_NUM[5].PWM_CDTY = (uint32_t)((180 + 80) / 2); /// 180 is max value, 80 min value 
	
	PWM->PWM_ENA = PWM_ENA_CHID5;// Enable PWM channel 5.
}


void pwm_set_duty_cycle(uint32_t joystick_pos) {
	
	uint32_t duty_cycle = (uint32_t)(0.38*(float)joystick_pos + 80.0);
	if (duty_cycle > max_duty_cycle_value) {
		PWM->PWM_CH_NUM[5].PWM_CDTY = max_duty_cycle_value;
	}
	else if (duty_cycle < min_duty_cycle_value) {
		PWM->PWM_CH_NUM[5].PWM_CDTY = min_duty_cycle_value;
	}
	else if (duty_cycle > 125 && duty_cycle < 155) {
		PWM->PWM_CH_NUM[5].PWM_CDTY = mean_duty_cycle_value;
	}
	else {
		PWM->PWM_CH_NUM[5].PWM_CDTY = duty_cycle;
	}
	
	//printf("duty cycle calc: %d\r", duty_cycle);
}

