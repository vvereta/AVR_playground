#ifndef LIB_ATMEGA328P_H
# define LIB_ATMEGA328P_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int add(int a, int b);
int sub(int a, int b);
void init_uart(const unsigned long baudrate);
void USART_puts(char* str);
#endif