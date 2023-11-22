#include "can.h"
#include <stdint.h>
#include "mcp.h"
#include <stdio.h>

#define F_CPU 16000000
#define BAUDRATE        250000
#define TOT_TQ    16
#define PROPAG  1
#define PS1     5
#define PS2     6

//Used some of the same numbers on Time quantas as other groups
int can_init() {
	int err = 0;
	err = mcp2515_init();
    uint8_t brp = (F_CPU / (2 * TOT_TQ * BAUDRATE)) -1; 

    mcp2515_write(MCP_CNF1, SJW4 | brp);
    mcp2515_write(MCP_CNF2, BTLMODE | SAMPLE_3X | (PS1 << 3) | PROPAG);
    mcp2515_write(MCP_CNF3, WAKFIL_DISABLE | PS2);
	
	mcp2515_mode_select(MODE_NORMAL);
	mcp2515_bit_modify(MCP_CANINTE, 0b11111111, 0b00000001); //rx interrupt enable
	return err;
}

void can_write(struct Message *msg) {
	if (msg->length > 8) {
		printf("ERROR, message lengthto high \r\n");
	}

	mcp2515_write(MCP_TXB0SIDH, msg->id >> 3);
	mcp2515_write(MCP_TXB0SIDL, (msg->id & 0xff) << 5);
	mcp2515_write(MCP_TXB0DLC, msg->length);
	
	for (int i = 0; i < msg->length; i++) {
		mcp2515_write(MCP_TXB0D0+i, msg->data[i]);
	}
	mcp2515_rts(0);
	if (mcp2515_read(MCP_CANINTF) & 0b00000000) {
		printf("Message error \r\n");
	}
}

struct Message can_read() {
	struct Message msg_read;
	uint8_t low = mcp2515_read(MCP_RXB0SIDL);
	uint8_t high = mcp2515_read(MCP_RXB0SIDH);
	msg_read.id = (high << 8) | low;
	msg_read.length = mcp2515_read(MCP_RXB0DLC);
	for (int i = 0; i < msg_read.length; i++) {
		msg_read.data[i] = mcp2515_read(MCP_RXB0D0+i); //Bruke alle 8 registre RXB0D0-8
	}
	return msg_read;
}


void can_loopback_test() {
	mcp2515_reset();
	mcp2515_mode_select(MODE_LOOPBACK);
	struct Message m_w = {
		.id = 1,
		.length = 8,
		.data = "hello"
	};
	struct Message m_r = {0};
	can_write(&m_w);
	m_r = can_read();
	
	printf("msg received ID:  %d\t", m_r.id);
	printf("msg received data %s\r\n", m_r.data);
}