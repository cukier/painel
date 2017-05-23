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
}

void init(void)
{
	DDRD |= _BV(DDD2);
	DDRD |= _BV(DDD3);
	DDRD |= _BV(DDD4);
	DDRD |= _BV(DDD5);
	
	uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));
	sei();
	
	return;
}

int main(void)
{
	uint8_t m_addr;
	
	m_addr = 0;
	init();
	
	while (1)
	{
		set_addr(m_addr);
		uart_printf("addr %u\n\r", m_addr);
		m_addr++;
		
		if (m_addr > 8)
		{
			m_addr = 0;
		}
		
		_delay_ms(1000);
	}
	
	return -1;
}

