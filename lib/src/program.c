#include "program.h"

int LED = 1<<5;

ISR(TIMER1_OVF_vect)
{
	PORTB ^= (LED);
}

void	init_led(void)
{
	DDRB |= LED;
	PORTB |= LED;
}

void	init_timer(void)
{
	cli();
	TCCR1B |= (1 << CS12);	// 256 prescaler 
	TIMSK1 |= (1 << TOIE1);	// enable timer overflow interrupt
	sei();
}

int	main(void)
{
	init_led();
	init_timer();
	add(5, 2);
	while (1)
	;
	return (0);
}