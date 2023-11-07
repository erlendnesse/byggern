/*
 * dac.c
 *
 * Created: 07.11.2023 15:20:06
 *  Author: jonassfr
 */ 
#include "dac.h"
#include "sam.h"
#include <stdio.h>

int dac_init() {
	//free running mode, enable channel an write data in DACC conversion data register
	DACC->DACC_MR |= DACC_MR_USER_SEL_CHANNEL1 | DACC_MR_STARTUP_16; //Set startup time if not working?
	
	//enable channel 1 
	DACC->DACC_CHER |= DACC_CHER_CH1;
	
	//enable clock for DAC
	PMC->PMC_PCR |= (1<<28) | (38);
	
	// enable power adc 
	PMC->PMC_PCER1 |= PMC_PCER1_PID38;
	
	if (!(DACC->DACC_CHSR)) {
		printf("ERROR: Channel not enabled");
		return -1;
	}
	return 0;
}

void dac_write(uint16_t value) {
	DACC->DACC_CDR = value;
}