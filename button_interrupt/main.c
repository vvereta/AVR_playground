#include <avr/io.h>
#include <avr/interrupt.h>

#define BUTTON 1 << 2
#define LED 1 << 5

unsigned int status;

ISR(INT0_vect)
{
	PORTB ^= (LED);
}

int		main(void)
{
  cli();
  DDRB |= LED;
  DDRD &= ~(BUTTON);
  PORTD |= (BUTTON);
  EICRA = 0x2;
  EIMSK = 0x01;
  EIFR = 0;
  sei();
	
	while (1)
		;
	return (0);
}