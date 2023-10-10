#include "can.h"
#include <stdint.h>
#include "mcp.h"
#include <stdio.h>


int can_init() {
    int err = 0;
    err = mcp2515_init();
	
	
	mcp2515_bit_modify(MCP_CANINTE, 0b00000001, 0b00000001); //rx interrupt enable
    mcp2515_mode_select(MODE_NORMAL);

    

    return err;
}

void can_write(struct Message msg) {
    if (msg.length > 8) {
        printf("ERROR, message length value to high \r\n");
        return -1;
    }
	//mcp2515_write(BFPCTRL, 0b00000101); //enable interrupt on rx0bf pin. Not needed since we only need interrupt when received message on caninte rx.
	// mcp2515_bit_modify(MCP_TXB0CTRL, 0b00001011, 0b000001011); //sjekke om denne også trengs?

	mcp2515_write(MCP_TXB0SIDH, msg.id);
	mcp2515_write(MCP_TXB0SIDL, 0);
	mcp2515_write(MCP_TXB0DLC, msg.length); 

    for (int i = 0; i < msg.length; i++) {
	    mcp2515_write(MCP_TXB0D0+i, msg.data[i]);
    }
	
	if (mcp2515_read(MCP_CANINTF) & 0b10100000) {
		printf("Message error \r\n");	
	}
}

struct Message can_read() {
    struct Message msg_read;
    msg_read.id = (mcp2515_read(MCP_RXB0SIDH) << 3) + (mcp2515_read(MCP_RXB0SIDL) >> 5);
    msg_read.length = mcp2515_read(MCP_RXB0DLC);

    for (int i = 0; i < msg_read.length; i++) {
	    msg_read.data[i] = mcp2515_read(MCP_RXB0D0+i); //Bruke alle 8 registre RXB0D0-8
    }

    return msg_read;
}


void can_loopback_test(char *str) {
    mcp2515_mode_select(MODE_LOOPBACK);

    struct Message m_w = {
        .id = 2000,
        .length = 8,
        .data = str
    };

    struct Message m_r = {0};

    can_write(m_w);
    m_r = can_read();

    printf("msg received ID:  %d\t", m_r.id);
    printf("msg received data %s\r\n", m_r.data);
}
