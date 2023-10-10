#include "can.h"
#include <stdint.h>
#include "mcp.h"
#include <stdio.h>


int can_init() {
	int err = 0;
	err = mcp2515_init();
	uint8_t cnf1_data = 0b0;
	uint8_t cnf2_data = 0b0;
	uint8_t cnf3_data = 0b0;
	mcp2515_bit_modify(MCP_CNF1, 0b0, cnf1_data);
	mcp2515_bit_modify(MCP_CNF2, 0b0, cnf2_data);
	mcp2515_bit_modify(MCP_CNF3, 0b0, cnf3_data);
	
	if (
	((mcp2515_read(MCP_CNF1) & cnf1_data) == cnf1_data) ||
	((mcp2515_read(MCP_CNF2) & cnf2_data) == cnf2_data) || 
	((mcp2515_read(MCP_CNF3) & cnf3_data) == cnf3_data)
	) 
	{
		
	}
	
	mcp2515_mode_select(MODE_NORMAL);
	mcp2515_bit_modify(MCP_CANINTE, 0b11111111, 0b00000001); //rx interrupt enable
	return err;
}

void can_write(struct Message *msg) {
	if (msg->length > 8) {
		printf("ERROR, message length value to high \r\n");
	}
	mcp2515_bit_modify(MCP_TXB0CTRL, 0b00001000, 0b000001000); //remove on normal mode?
	mcp2515_write(MCP_TXB0SIDH, msg->id / 8);
	mcp2515_write(MCP_TXB0SIDL, (msg->id % 8) << 5);
	mcp2515_write(MCP_TXB0DLC, msg->length);
	
	for (int i = 0; i < msg->length; i++) {
		mcp2515_write(MCP_TXB0D0+i, msg->data[i]);
	}
	if (mcp2515_read(MCP_CANINTF) & 0b10100000) {
		printf("Message error \r\n");
	}
}

struct Message can_read() {
	struct Message msg_read;
	uint8_t low = mcp2515_read(MCP_RXB0SIDL)/0b100000;
	uint8_t high = mcp2515_read(MCP_RXB0SIDH);
	msg_read.id = high * 0b1000 + low;
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
		.id = 10,
		.length = 8,
		.data = "FUCKYO"
	};
	struct Message m_r = {0};
	can_write(&m_w);
	m_r = can_read();
	
	printf("msg received ID:  %d\t", m_r.id);
	printf("msg received data %s\r\n", m_r.data);
}