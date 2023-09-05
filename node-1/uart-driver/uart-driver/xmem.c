#include <avr/io.h>
#include "xmem.h"

void xmem_init(void) {
	MCUCR |= (1 << SRE); //enable XMEM
	SFIOR |= (1 << XMM2); //bit masking
	printf("init.....   ");
	
	
	
}

void xmem_write() {
	volatile uint8_t *SRAM = (uint8_t *)0x1808;

	*SRAM = 0b11111100;
	
	
}
