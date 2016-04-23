#include <avr/io.h>
#include <avr/interrupt.h>

#define SHIFT_ENABLED PIND & _BV(PD5)

//shift up in		PD2/INT0
//shift down in		PD3/INT1
//shift enable in	PD5
//shift up out		PC4
//shift down out	PC5

void setup() {
	DDRC |= _BV(DDC4) | _BV(DDC5); //set PC4,5 as outputs
	DDRD &= ~(_BV(DDD2) | _BV(DDD3) | _BV(DDD5)); //set PD2,3,5 as inputs
	PORTD |= _BV(PORTD2) | _BV(PORTD3) | _BV(PORTD5); //set pull-ups on PD2,3,5
	EICRA = 0x0A; //set falling edge interrupts on INT0,1
	EIMSK = 0x03; //enable INT0,1
	sei(); //enable global interrupts
}

void loop() {
	
}

ISR(INT0_vec) {
	if(SHIFT_ENABLED) {
		
	}
}

ISR(INT1_vec) {
	if(SHIFT_ENABLED) {
		
	}
}