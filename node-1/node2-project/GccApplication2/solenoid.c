#include "solenoid.h"

#include "sam.h"
#include "delay.h"



void solenoid_init() {
    //Pio Enable Register
    PIOA->PIO_PER |= PIO_PA14;

    //enable Output Enable Register
    PIOA->PIO_OER |= PIO_PA14;

    //Set Output Data Register
    PIOA->PIO_SODR |= PIO_PA14;
};

void solenoid_shoot(int button){
    //generates short pulse if button is pressed
    if (button) {
        PIOA->PIO_CODR |= PIO_PA14;
        delay_ms(100);
        PIOA->PIO_SODR |= PIO_PA14;
    }
}
