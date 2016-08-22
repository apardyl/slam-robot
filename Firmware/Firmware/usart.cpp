/*
 * usart.cpp
 *
 * Created: 2016-08-21 15:06:01
 *  Author: Adam
 */ 

#include "usart.h"
#include <avr/io.h>

#include <avr/interrupt.h>

FIFO FIFOTxDebugUsart(32);
FIFO FIFORxDebugUsart(32);

void initDebugUSART() {
	UBRR3 = 0x0000;
	UCSR3B = (1<<RXEN3) | (1<<TXEN3) | (1<<TXCIE3) | (1<<RXCIE3);
	UCSR3C = (1<<UCSZ30) | (1<<UCSZ31);
}

void sendDebugUSART() {
	if(!FIFOTxDebugUsart.isEmpty()) UDR3 = FIFOTxDebugUsart.pop();
}

ISR(USART3_TX_vect) {
	if(!FIFOTxDebugUsart.isEmpty()) UDR3 = FIFOTxDebugUsart.pop();
}

ISR(USART3_RX_vect) {
	FIFORxDebugUsart.insert(UDR3);
}

FIFO FIFORxGPSUsart(32);

void initGPSUSART() {
	UBRR0 = 0x0067;
	UCSR0B = (1<<RXEN0) | (1<<RXCIE0);
	UCSR0C = (1<<UCSZ00) | (1<<UCSZ01);
}

ISR(USART0_RX_vect) {
	FIFORxGPSUsart.insert(UDR0);
}