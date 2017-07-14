#include <avr/io.h>
#include <avr/interrupt.h>

#define pinA 1 << 2
#define pinB 1 << 3
#define LED 1<<5;

volatile unsigned char direction = 0;

ISR		(TIMER0_OVF_vect)  // T0 timer overflow interrupt
{
	PORTB &=~(LED);
}

ISR		(TIMER0_COMP_vect)  // T0 timer compare interrupt
{
	PORTB |=(LED);  
}

ISR		(TIMER2_OVF_vect)  /*check encoder*/
{
	ask_encoder();
} 

void	init_ports(void)
{
	DDRD &= ~(pinA);
	DDRD &= ~(pinB);
	PORTD |= (pinA) | (pinB);
}

void	init_led(void)
{
	DDRB |= LED;
}

void	set_timers(void)
{
	TCCR2B |= CS22;
	TIMSK2 |= TOIE;
}

void	all_init(void)
{
	//init_ports();
	init_led();
	set_timers();
}

int		main(void)
{
	all_init();
	
	while (1)
		;
	return (0);
}