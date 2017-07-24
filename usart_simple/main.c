#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>

int LED = 1<<7;
//int LED = 1<<5;

static void init_uart(const unsigned long baudrate) {
    const uint16_t ubrr = F_CPU/8/baudrate - 1;
    
    UBRR0H = ubrr >> 8;
    UBRR0L = ubrr & 0xff;
    UCSR0A |= 1 << U2X0;
    
    UCSR0B = 1 << TXEN0;
    
    /* Set frame format: 8data, 1stop bit */
    UCSR0C = 3 << UCSZ00;
}

void USART_putc(unsigned char data)
{
    // wait for an empty buffer
    while ( !(UCSR0A & (1 << UDRE0)) );
    
    // put the data into the buffer = send it
    UDR0 = data;
}

void USART_puts(char* str)
{
    while(*str)
        USART_putc(*str++);
}

ISR(TIMER1_OVF_vect)	
{
    PORTB ^= (LED);
    USART_puts("Message\n\r");
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
