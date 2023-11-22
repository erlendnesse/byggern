/*
 * dac.h
 *
 * Created: 07.11.2023 15:19:58
 *  Author: jonassfr
 */ 


#ifndef DAC_H_
#define DAC_H_

#include <stdint.h>


int dac_init();
void dac_write(uint16_t value);


#endif /* DAC_H_ */