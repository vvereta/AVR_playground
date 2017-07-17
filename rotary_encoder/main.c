#include <avr/io.h>
#include <avr/interrupt.h>

#define pinA 1 << 3
#define pinB 1 << 4
#define LED 1<<6;

volatile unsigned char	pwm = 127;

unsigned char	ask_encoder(void)
{
	static unsigned char	last_state = 0;
	unsigned char			current_state;

	current_state = digitalRead(encoder0PinA);
	if ((last_state == LOW) && (current_state == HIGH))
	{
		if (digitalRead(encoder0PinB) == LOW)
			pwm--;
		else
			pwm++;
	}
	last_state = current_state;
	return (pwm);
}

ISR		(INT1_vect)  /*check encoder*/
{
	OCR0A = ask_encoder();
} 

void	init_ports(void)
{
	DDRD &= ~(pinA);
	DDRD &= ~(pinB);
	PORTD |= (pinA) | (pinB);
}

void	init_led(void)
{
	DDRD |= LED;
}

void	set_timers(void)
{
	TCCR0A |= _BV(COM0A1) | _BV(WGM00) | _BV(WGM01);
	TCCR0B |= _BV(CS00);
	OCR0A = pwm;
}

void	set_interrupt(void)
{
	EICRA |= (1 << ISC10) //Any logical change on INT1
	EIMSK |= (1 << INT1);//External Interrupt Request 1 Enable
	EIFR = 0; //Clear flags
}

void	all_init(void)
{
	cli();
	init_ports();
	init_led();
	set_timers();
	set_interrupt();
	sei();
}

int		main(void)
{
	all_init();
	while (1)
		;
	return (0);
}