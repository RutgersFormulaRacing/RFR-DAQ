#define F_CPU	8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

//check PD5 (shift enable)
#define SHIFT_ENABLED (PIND & _BV(PD5))
//set 16 bit timer to CTC mode and set timer prescaler to 64
#define TIMER_ON _BV(WGM12) | _BV(CS11) | _BV(CS10)

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
	OCRIA = 100*8000000/64000; //set pulse width to 100ms with 8MHz clock and 64 prescaler
	TIMSK |= _BV(OCIE1A);
	sei(); //enable global interrupts
}

void loop() 
{
	
}

//shift up
ISR(INT0_vec) {
	if(SHIFT_ENABLED) {
		TCNT1 = 0x0;
		TCCR1B = TIMER_ON;
		PORTC |= _BV(PC4);
	}
}

//shift down
ISR(INT1_vec) {
	if(SHIFT_ENABLED) {
		TCNT1 = 0x0;
		TCCR1B = TIMER_ON;
		PORTC |= _BV(PC5);
	}
}

ISR(TIMER1_OVF_vec) {
	PORTC &= ~(_BV(PC4) | _BV(PC5));
	TCCR1B = 0x0;
}