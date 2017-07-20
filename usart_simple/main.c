#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>

int LED = 1<<7;

static void init_uart(const unsigned long baudrate) {
    const uint16_t ubrr = F_CPU/8/baudrate - 1;
    
    UBRR0H = ubrr >> 8;
    UBRR0L = ubrr & 0xff;
    UCSR0A |= 1 << U2X0;
    
    UCSR0B = 1 << TXEN0;
    
    /* Set frame format: 8data, 1stop bit */
    UCSR0C = 3 << UCSZ00;
}

/* Primitive synchronous print */
static int print_polling(const char str[]) {
    size_t i = 0;
    const size_t N = strlen(str);
    
    for (i = 0; i < N; i++) {
        UDR0 = str[i];
        while (!(UCSR0A & (1 << UDRE0)));
    }
    
    return N;
}

ISR(TIMER1_OVF_vect)	
{
    PORTB ^= (LED);
    print_polling("Message\r\n");
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
    init_uart(9600);
	while (1)
	   ;
	return (0);
}
