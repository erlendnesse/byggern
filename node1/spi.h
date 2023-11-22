/*
 * spi.h
 *
 * Created: 03.10.2023 09:57:18
 *  Author: erleness
 */ 


#ifndef SPI_H_
#define SPI_H_

#include <stdint.h>

void spi_init();

void spi_write(uint8_t data);

uint8_t spi_read();

void spi_ss_set(uint8_t value);



#endif /* SPI_H_ */