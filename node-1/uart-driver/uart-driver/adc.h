/*
 * adc.h
 *
 * Created: 12.09.2023 11:49:07
 *  Author: jonassfr
 */

#include <stdint.h>


#ifndef ADC_H_
#define ADC_H_

void adc_init();

uint8_t adc_read(uint8_t channel);
		
		


#endif /* ADC_H_ */