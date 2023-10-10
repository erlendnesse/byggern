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
		printf(" MCP2515 is NOT in configuration mode after reset !\n\r");
		return -1;
	}
	
	
	// More initialization
	
	
	return 0;
}

void mcp2515_write(uint8_t address, uint8_t data)
{
	spi_ss_set(0);
	
	spi_write(MCP_WRITE);
	spi_write(address);
	spi_write(data);
	
	spi_ss_set(1);
	
}


uint8_t mcp2515_read(uint8_t address)
{
	uint8_t result;
	spi_ss_set(0);
	
	spi_write(MCP_READ); // Send read instruction
	spi_write(address); // Send address
	result = spi_read(); // Read result
	spi_ss_set(1);
	
	return result;
}


void mcp2515_reset() {
	
	spi_ss_set(0);
	
	spi_write(MCP_RESET);
	
	spi_ss_set(1);
}

void mcp2515_rts(int buffer){
	
	spi_ss_set(0);
	uint8_t data;
	
	if( buffer == 0) {
		data = MCP_RTS_TX0;
	}
	else if (buffer == 1) {
		data = MCP_RTS_TX1;
		
	}
	else if (buffer == 2) {
		data = MCP_RTS_TX2;
	}
	else {
		printf("Not correct buffer in function mcp2515_rts, buffer value: %d\r\n", buffer);
	}
	
	spi_write(data);
	spi_ss_set(1);
}

uint8_t mcp2515_read_status() {
	spi_ss_set(0);
	
	spi_write(MCP_READ_STATUS);
	uint8_t status_data = spi_read();
	
	spi_ss_set(1);
	
	return status_data;
}

void mcp2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data) {
	spi_ss_set(0);
	spi_write(MCP_BITMOD);
	spi_write(address);
	spi_write(mask);
	spi_write(data);
	spi_ss_set(1);
}


//Setter modus ved � maske CANCTRL-registeret med 0b11100000 (bare 3 MSB som gjelder) med moduser definert i mcp2515.h
void mcp2515_mode_select(uint8_t mode) {
	mcp2515_bit_modify(MCP_CANCTRL, 0b11100000, mode);
}



