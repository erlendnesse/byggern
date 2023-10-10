#include "can.h"
#include <stdint.h>
#include "mcp.h"



void mcp2515_transmission(struct Message msg) {
	uint8_t BFPCTRL = 0x0c;
	
	mcp2515_bit_modify(MCP_CANINTE, 0b00000101, 0b00000101); //rx and tx interrupt enable
	mcp2515_write(BFPCTRL, 0b00001111); //enable interrupt //sjekke om disse trengs?
	mcp2515_bit_modify(MCP_TXB0CTRL, 0b00001011, 0b000001011); //sjekke om denne også trengs?


	uint8_t TXB0SIDH = 0x31;
	uint8_t TXB0SIDL = 0x32;
	uint8_t TXB0DM = 0x36;
	uint8_t TXB0DLC = 0x35;
	
	
	mcp2515_write(TXB0SIDH, msg.id);
	mcp2515_write(TXB0SIDL, 0);
	mcp2515_write(TXB0DLC, msg.length); 
	mcp2515_write(TXB0DM, msg.data[0]);

	//mcp2515_rts(0);
	
	if (MCP_TXB0CTRL & 0b01110000) {
		printf("Transmission error \r\n");	
	}
}

struct Message mcp2515_reception() {
    struct Message msg_read;

	uint8_t BFPCTRL = 0x0c;
	uint8_t RXB0SIDH = 0x61;
	uint8_t RXB0SIDL = 0x62;
	uint8_t RXB0DM = 0x66; // denne m� inkrementeres for hver byte i forhold til data lengde, husk og fjerne tidligere bytes p� adressen etter ferdig.
	
	
	
	uint8_t interrupt_pins = mcp2515_read(BFPCTRL) & 0b00110000;
	while (interrupt_pins) {
	}
	msg_read.data[0] = mcp2515_read(RXB0DM); //Bruke alle 8 registre RXB0D0-8

    return msg_read;
}


void mcp2515_print(char *str) { ///Fjerne denne og heller ha 8 bytes max lengde p� reception og read
    struct Message m_w = {
        .id = 0x11,
        .length = 0, //betyr ingenting
        .data = str
    };

    struct Message m_r = {0};

	char *c = str;
	char print_str[10] = "";
	int i = 0;
	while (*c != '\0')
	{
		mcp2515_transmission(m_w);
		m_r = mcp2515_reception();
		printf("%c\r\n", m_r.data[i]);
		c++;
		i++;
		_delay_ms(500);
	}
	
	//printf("output %s \r\n", print_str);
}
