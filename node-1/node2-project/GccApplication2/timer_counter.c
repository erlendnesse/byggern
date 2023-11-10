/*
 * timer_counter.c
 *
 * Created: 24.10.2023 09:31:10
 *  Author: erleness
 */ 

#include "timer_counter.h"
#include "sam.h"

//value 232-1 and passes to zero, an overflow occurs
//and the COVFS bit in the TC Status Register (TC_SR) is set.

// TCCLKS bits in the TC Channel Mode Register (TC_CMR)

//CLKEN and the CLKDIS commands in the TC Channel Control Register (TC_CCR)

//Compare RC Trigger: RC is implemented in each channel and can provide a trigger when the counter value
//matches the RC value if CPCTRG is set in the TC_CMR

//Waveform mode is entered by setting the TC_CMRx.WAVE bit.

//TC0 TIOA0 PB25 B

//timer counter is not used


void timer_counter_init() {
	//REG_TC0_CCR0
	
	PMC->PMC_PCR = ID_PIOB;
	//PIOB->PIO_ABSR |= 1 << 25; //kanskje bare piss?
	PIOB->PIO_PER |= 1 << 25;
	PIOB->PIO_OER |= 1 << 25;
	//*k |= 1;
	//*REG_TC0_CMR0 |= 1 << 14 | 1 << 15 | 3 << 16; 
	//*REG_TC0_IER0 |= 1 << 2;
	*REG_TC0_RC0 = 0xaf;
	
	//Kan bruke TC_SR til feilsjekk(status register)
	
}