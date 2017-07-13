#include <avr/io.h>
#include <avr/interrupt.h>

#define BUTTON 1 << 2
#define LED 1 << 5

ISR(INT0_vect)
{
	PORTB ^= (LED);
}

void		led_init(void)
{
	DDRB |= LED;
	PORTB |= LED;
}

void		button_init(void)
{
	DDRD &= ~(BUTTON);
	PORTD |= (BUTTON);
}

void		int_init(void)
{
	EICRA = 0x2;
	EIMSK = 0x01;
	EIFR = 0;
}

void		all_init(void)
{
	cli();
	led_init();
	button_init();
	int_init();
	sei();
}

int		main(void)
{
	all_init();
	
	while (1)
		;
	return (0);
}