#include "lib_atmega328p.h"

void init_uart(const unsigned long baudrate) {
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