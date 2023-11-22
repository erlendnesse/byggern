/*
 * spi.c
 *
 * Created: 03.10.2023 09:57:29
 *  Author: erleness
 */ 

#include "spi.h"
#include <avr/io.h>


#define SS_PIN PB4
#define MOSI_PIN PB5
#define SCK_PIN PB7



void spi_init(void)
{
	/* Set MOSI and SCK output, all others input */
	DDRB |=  (1 << MOSI_PIN) | (1 << SCK_PIN) | (1 << SS_PIN);
	
	//maybe set SPIE to 1, interrupt enable
	
	
	// Enable SPI, Master, set clock rate fck/16 
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
	spi_ss_set(1);
}

void spi_ss_set(uint8_t value) {
	if (value == 1) {
		// Skrur ss høyt, dvs. setter cs_ på MCP2515 høy, skrur av 
		PORTB |= (1 << SS_PIN);
	}
	if (value == 0) {
		PORTB &= ~(1 << SS_PIN);
	}
}

void spi_write(uint8_t data)
{
	// Start transmission 
	SPDR = data;
	// Wait for transmission complete 
	while(!(SPSR & (1<<SPIF)));
}

uint8_t spi_read() {
	//dummy byte transmit to start reading
	spi_write(0x00);
	// Wait for reception complete
	while(!(SPSR & (1<<SPIF)));
	// Return data register 
	uint8_t sp = SPDR;
	return sp;
	
	
}

