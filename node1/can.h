#ifndef CAN_H_
#define CAN_H_

#include <stdint.h>
#define  ID_POSITION 1


struct Message {
	uint16_t id;
	uint8_t length;
	uint8_t data[8];
};


int can_init();
void can_write(struct Message * msg);
struct Message can_read();
void can_loopback_test();


#endif