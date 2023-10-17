/*
 * IncFile1.h
 *
 * Created: 19.09.2023 10:36:21
 *  Author: jonassfr
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_

struct pos {
	int x_pos;
	int y_pos;
};

typedef enum{
	NEUTRAL = 0,
	LEFT,
	RIGHT,
	UP,
	DOWN
} dir_t;

dir_t dir();

void joystick_init();
struct pos pos_read(void);


#endif /* INCFILE1_H_ */