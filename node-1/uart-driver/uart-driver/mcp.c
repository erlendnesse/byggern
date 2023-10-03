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

void mcp2515_write(uint8_t address, uint8_t data)

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
	}