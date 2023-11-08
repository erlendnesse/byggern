/*
 * interrupt.h
 *
 * Created: 17.10.2023 13:37:36
 *  Author: erleness
 */ 


#ifndef INTERRUPT_H_
#define INTERRUPT_H_

void interrupt_init();
extern volatile int interruptCount;

extern volatile int game_finished;

#endif /* INTERRUPT_H_ */