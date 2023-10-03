/*
 * CFile1.c
 *
 * Created: 03.10.2023 13:22:06
 *  Author: erleness
 */ 


#include "mcp2515.h"
#include "spi.h"
#include "mcp.h"
#include <stdio.h>
#include <util/delay.h>

//MCP init innit?

int mcp2515_init()
{
	spi_init(); // Initialize SPI
	mcp2515_reset(); // Send reset - command
	_delay_ms(500);
	
	// Self - test
	uint8_t value = mcp2515_read(MCP_CANSTAT);
	if ((value & MODE_MASK) != MODE_CONFIG)
	{
		printf(" MCP2515 is NOT in configuration mode after reset !\n");
		return -1;
	}
	
	
	// More initialization
	
	
	return 0;
}

void mcp2515_write(uint8_t address, uint8_t data){	spi_ss_set(0);		spi_write(MCP_WRITE);	spi_write(address);	spi_write(data);		spi_ss_set(1);	}

uint8_t mcp2515_read(uint8_t address)
{
	uint8_t result;
	spi_ss_set(0);
	
	spi_write(MCP_READ); // Send read instruction
	spi_write(address); // Send address
	result = spi_read(); // Read result
	spi_ss_set(1);
	
	return result;
}void mcp2515_reset() {		spi_ss_set(0);		spi_write(MCP_RESET);		spi_ss_set(1);}void mcp2515_rts(int buffer){		spi_ss_set(0);	uint8_t data;		if( buffer == 0) {		data = MCP_RTS_TX0;	}	else if (buffer == 1) {		data = MCP_RTS_TX1;			}	else if (buffer == 2) {		data = MCP_RTS_TX2;	}	else {		printf("Not correct buffer in function mcp2515_rts, buffer value: %d\r\n", buffer);	}		spi_write(data);	spi_ss_set(1);}uint8_t mcp2515_read_status() {	spi_ss_set(0);		spi_write(MCP_READ_STATUS);	uint8_t status_data = spi_read();		spi_ss_set(1);		return status_data;}void mcp2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data) {	spi_ss_set(0);	spi_write(MCP_BITMOD);	spi_write(address);	spi_write(mask);	spi_write(data);	spi_ss_set(1);}//Setter modus ved å maske CANCTRL-registeret med 0b11100000 (bare 3 MSB som gjelder) med moduser definert i mcp2515.hvoid mcp2515_mode_select(uint8_t mode) {	mcp2515_bit_modify(MCP_CANCTRL, 0b11100000, mode);}void mcp2515_transmission(uint8_t id, uint8_t data) {	uint8_t BFPCTRL = 0x0c;		mcp2515_bit_modify(MCP_CANINTE, 0b00000101, 0b00000101); //rx and tx interrupt enable	mcp2515_write(BFPCTRL, 0b00001111); //enable interrupt	mcp2515_bit_modify(MCP_TXB0CTRL, 0b00001011, 0b000001011); 	uint8_t TXB0SIDH = 0x31;	uint8_t TXB0SIDL = 0x32;	uint8_t TXB0DM = 0x36;	uint8_t TXB0DLC = 0x35;			mcp2515_write(TXB0SIDH, id);	mcp2515_write(TXB0SIDL, 0);	mcp2515_write(TXB0DLC, 1);	mcp2515_write(TXB0DM, data);	//mcp2515_rts(0);		if (MCP_TXB0CTRL & 0b01110000) {		printf("Transmission error \r\n");		}}uint8_t mcp2515_reception(uint8_t id) {	uint8_t BFPCTRL = 0x0c;	uint8_t RXB0SIDH = 0x61;	uint8_t RXB0SIDL = 0x62;	uint8_t RXB0DM = 0x66; // denne må inkrementeres for hver byte i forhold til data lengde, husk og fjerne tidligere bytes på adressen etter ferdi.				uint8_t interrupt_pins = mcp2515_read(BFPCTRL) & 0b00110000;	while (interrupt_pins) {	}	uint8_t data = mcp2515_read(RXB0DM);}void mcp2515_print(char *str) { ///Fjerne denne og heller ha 8 bytes max lengde på reception og read
	char *c = str;
	char print_str[10] = "";
	int i = 0;
	while (*c != '\0')
	{
		mcp2515_transmission(0x11, c[i]);
		print_str[i] = mcp2515_reception(0x11);
		printf("%c\r\n", print_str[i]);
		c++;
		i++;
		_delay_ms(500);
	}		//printf("output %s \r\n", print_str);}