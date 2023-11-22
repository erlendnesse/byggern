/*
 * PWM.h
 *
 * Created: 24.10.2023 08:42:17
 *  Author: erleness
 */


#ifndef PWM_SERVO_H_
#define PWM_SERVO_H_
#include "sam.h"




void PWM_init(void);
void PWM_duty_cycle_update(int CDTYUPD);
void pwm_set_duty_cycle(uint32_t joystick_pos);


#endif /* PWM_SERVO_H_ */