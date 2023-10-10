/*
 * spi.c
 *
 * Created: 03.10.2023 09:57:29
 *  Author: erleness
 */ 

#include "spi.h"
#include <avr/io.h>

//SPI When configured as a Master, the SPI interface has no automatic control of the SS line. This
//must be handled by user software before communication can start

//When this is done, writing a byte to the SPI Data Register starts the SPI clock generator

// After shifting one byte, the SPI clock generator stops, setting the End of Transmission Flag (SPIF)

//If the SPI Interrupt Enable bit (SPIE) in the SPCR Register is set, an interrupt is requested

//The Master may continue to shift the next byte by writing it into SPDR, or signal the end of packet by pulling high the Slave Select, SS line.


//When receiving data, however, a received character must be
//read from the SPI Data Register before the next character has been completely shifted in. Otherwise, the first byte is lost.


//MOSI OUTPUT
//SCK OUTPUT
//SS OUTPUT

#define SS_PIN PB4
#define MOSI_PIN PB5
#define SCK_PIN PB7



void spi_init(void)
{
	/* Set MOSI and SCK output, all others input */
	DDRB |=  (1 << MOSI_PIN) | (1 << SCK_PIN) | (1 << SS_PIN);
	
	//maybe set SPIE to 1, interrupt enable
	
	
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
	spi_ss_set(1);
}

void spi_ss_set(uint8_t value) {
	if (value == 1) {
		//printf("value 1\r\n");
		// Skrur ss høyt, dvs. setter cs_ på MCP2515 høy, skrur av 
		PORTB |= (1 << SS_PIN);
	}
	if (value == 0) {
		//printf("value 2\r\n");
		PORTB &= ~(1 << SS_PIN);
	}
}

void spi_write(uint8_t cData)
{
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
}

uint8_t spi_read() {
	//dummy byte transmit to start reading
	spi_write(0x00);
	/* Wait for reception complete*/
	while(!(SPSR & (1<<SPIF)));
	/* Return data register */
	uint8_t sp = SPDR;
	return sp;
	
	
}

