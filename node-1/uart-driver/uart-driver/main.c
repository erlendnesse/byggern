/*
 * uart-driver.c
 *
 * Created: 29.08.2023 15:05:08
 * Author : jonassfr
 */ 

#include "uart_driver.h"
#include <util/delay.h>
#include "xmem.h"
#include <avr/io.h>
#include "adc.h"
#include "joystick.h"
#include "oled.h"

void oled_goto_column(int column) {
	write_command(0x00 + (column % 16)); // Lower nibble
	write_command(0x10 + (column / 16)); // Higher nibble
}

int main(void)
{
	int sleep_time = 1000;
    _delay_ms(sleep_time);
	usart_init(MYUBRR);
	

	xmem_init();
	adc_init();
	if (SRAM_test()) {
		printf("SRAM test failed\r\n");
		return 0;
	}
	oled_init();
	
	PORTD |= (1 << PD5); //setup pullup for PD5 which is button input from Joystick
	//(PIND & (1 << 5)) >> 5 //Read input from button Joystick
	

	

    while (1) 
    {
		write_command(0x20); //velg modus
		write_command(0b10); //velg page adressing modus
		
		
		write_command(0xB3);
		write_command(0x00 + 0b0001); // Setter lower nibble for kolonne 97
		write_command(0x10 + 0b0110); // Setter higher nibble for kolonne 97
		
		for (int line = 0xB0; line < 0xB8; line++) {
			write_command(line);
			oled_goto_column(0);
			for (int i = 0; i < 128; i++) {
				write_data(0x01);
			}
		}
		
		
		
		

		//_delay_ms(sleep_time*2);
		//
		//test av chipselect på ADC. Setter PD5 høy, sender dette inn på 	
		
		//printf("ADC value CH0: %d\n\r", ch0);
		//printf("X(raw): %d, \t X(pos): %d, \t Y(raw): %d, \t Y(pos): %d \n\r", adc_read(0), (int)pos_read().x_pos, (int)adc_read(1), pos_read().y_pos);
		//printf("Direction: %d \r\n", dir());
		//printf("X: %d \t, Y: %d \r\n", pos_read().x_pos, pos_read().y_pos);
		//printf("Slider left: %d \t, Slider right: %d \r\n", adc_read(3), adc_read(2));
		

		
		
    }
	return 0;
}

