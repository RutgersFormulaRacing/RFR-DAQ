#include <avr/io.h>
#include <avr/interrupt.h>

//shift up in		PD2
//shift down in		PD3
//shift enable in	PD5
//shift up out		PC4
//shift down out	PC5

void setup() {
	DDRC |= 0x30; //set PC4,5 as outputs
	DDRD &= 0xD3; //set PD2,3,5 as inputs
	PORTD |= 0x0C; //set pull-ups on PD2,3
	EICRA = 0x0A; // set falling edge interrupts on INT0,1
}

void loop() {
	
}

ISR(INT0_vec) {
	
}

ISR(INT1_vec) {
	
}