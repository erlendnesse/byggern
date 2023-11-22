#include <avr/io.h>
#include "xmem.h"

void xmem_init(void) {
	MCUCR |= (1 << SRE); //enable XMEM
	SFIOR |= (1 << XMM2); //bit masking
	printf("-XMEM init-\n");	
}


/*Used for testing every pinout on xmem atmega*/
void xmem_write() {
	volatile uint8_t *SRAM = (uint16_t*)0x1800;
	*SRAM = 0b11111100;
	*SRAM = 0b11111100;
	*SRAM = 0b11111100;
	*SRAM = 0b11111100;
	*SRAM = 0b11111100;
	*SRAM = 0b11111100;
	*SRAM = 0b11111100;
	*SRAM = 0b11111100;
	*SRAM = 0b11111100;
}
