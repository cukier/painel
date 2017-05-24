/*
* painel.c
*
* Created: 23/05/2017 15:59:30
* Author : cuki
*/

#include "sys.h"
#include "uart.h"

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void set_addr(uint8_t addr)
{
	switch (addr)
	{
		case 0: //0000
		PORTD &= ~_BV(PORTD2);
		PORTD &= ~_BV(PORTD3);
		PORTD &= ~_BV(PORTD4);
		PORTD &= ~_BV(PORTD5);
		break;
		
		case 1: //0001
		PORTD |= _BV(PORTD2);
		PORTD &= ~_BV(PORTD3);
		PORTD &= ~_BV(PORTD4);
		PORTD &= ~_BV(PORTD5);
		break;
		
		case 2: //0010
		PORTD &= ~_BV(PORTD2);
		PORTD |= _BV(PORTD3);
		PORTD &= ~_BV(PORTD4);
		PORTD &= ~_BV(PORTD5);
		break;
		
		case 3: //0011
		PORTD |= _BV(PORTD2);
		PORTD |= _BV(PORTD3);
		PORTD &= ~_BV(PORTD4);
		PORTD &= ~_BV(PORTD5);
		break;
		
		case 4: //0100
		PORTD &= ~_BV(PORTD2);
		PORTD &= ~_BV(PORTD3);
		PORTD |= _BV(PORTD4);
		PORTD &= ~_BV(PORTD5);
		break;
		
		case 5: //0101
		PORTD |= _BV(PORTD2);
		PORTD &= ~_BV(PORTD3);
		PORTD |= _BV(PORTD4);
		PORTD &= ~_BV(PORTD5);
		break;
		
		case 6: //0110
		PORTD &= ~_BV(PORTD2);
		PORTD |= _BV(PORTD3);
		PORTD |= _BV(PORTD4);
		PORTD &= ~_BV(PORTD5);
		break;
		
		case 7: //0111
		PORTD |= _BV(PORTD2);
		PORTD |= _BV(PORTD3);
		PORTD |= _BV(PORTD4);
		PORTD &= ~_BV(PORTD5);
		break;
		
		case 8: //1000
		PORTD &= ~_BV(PORTD2);
		PORTD &= ~_BV(PORTD3);
		PORTD &= ~_BV(PORTD4);
		PORTD |= _BV(PORTD5);
		break;
	}
	
	return;
}

void set_clock(void)
{
	PORTB |= _BV(PORTB2);
	_delay_ms(1);
	PORTB &= ~_BV(PORTB2);
	
	return;
}

void set_clear(void)
{
	PORTB |= _BV(PORTB3);
	_delay_ms(1);
	PORTB &= ~_BV(PORTB3);
	
	return;
}

void serial_clock(void)
{
	PORTB |= _BV(PORTB1);
	_delay_ms(1);
	PORTB &= ~_BV(PORTB1);
	
	return;
}

void serial_out(uint8_t var)
{
	uint8_t cont;
	
	for (cont = 0; cont < 8; ++cont)
	{
		if ((_BV(7 - cont) & var) != 0)
		{
			PORTB |= _BV(PORTB0);
		}
		else
		{
			PORTB &= ~_BV(PORTB0);
		}
		
		serial_clock();
	}
	
	return;
}

void init(void)
{
	DDRD |= _BV(DDD2);
	DDRD |= _BV(DDD3);
	DDRD |= _BV(DDD4);
	DDRD |= _BV(DDD5);
	
	DDRB |= _BV(DDB0);
	DDRB |= _BV(DDB1);
	DDRB |= _BV(DDB2);
	DDRB |= _BV(DDB3);
	
	uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));
	sei();
	
	return;
}

void put_p(uint8_t a, uint8_t c)
{
	set_addr(a);
	serial_out(c);
	set_clock();
	
	return;
}

int main(void)
{
	uint8_t m_addr;
	
	m_addr = 0;
	init();
	
	while (1)
	{
		switch(m_addr++)
		{
			case 0:
			put_p(0, 0b10101010);
			put_p(1, 0b01010101);
			put_p(2, 0b10101010);
			put_p(3, 0b01010101);
			put_p(4, 0b10101010);
			_delay_ms(1000);
			break;
			
			case 1:
			put_p(0, 0b01010101);
			put_p(1, 0b10101010);
			put_p(2, 0b01010101);
			put_p(3, 0b10101010);
			put_p(4, 0b01010101);
			_delay_ms(1000);
			break;
			
			default:
			m_addr = 0;
			break;
		}
		
	}
	
	return -1;
}

