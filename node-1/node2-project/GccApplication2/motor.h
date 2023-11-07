/*
 * motor.h
 *
 * Created: 07.11.2023 14:48:21
 *  Author: jonassfr
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

#define MOTOR_SPEED_5V 65535
#define MOTOR_SPEED_0V 0

#include <stdint.h>

int motor_init();

void motor_set_speed(uint16_t speed);

void motor_set_dir(uint8_t direction);

void motor_enable(uint8_t bool);

int motor_read_encoder();

void motor_run(uint8_t dir);

#endif /* MOTOR_H_ */