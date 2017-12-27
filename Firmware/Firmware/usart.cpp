#include "usart.h"
#include <avr/io.h>

#include <avr/interrupt.h>

USART DebugUsart(250, 250);

void initDebugUSART() {
	UBRR3 = /*0x067;*/ 0x0000;
	UCSR3B = (1<<RXEN3) | (1<<TXEN3) | (1<<TXCIE3) | (1<<RXCIE3);
	UCSR3C = (1<<UCSZ30) | (1<<UCSZ31);
	DebugUsart.isBusy = false;
}

void sendDebugUSART() {
	if(DebugUsart.isBusy) return;
	if(!DebugUsart.tx.isEmpty()) {
		DebugUsart.isBusy = true;
		UDR3 = DebugUsart.tx.pop();
	}
}

ISR(USART3_TX_vect) {
	if(!DebugUsart.tx.isEmpty()) UDR3 = DebugUsart.tx.pop();
	else DebugUsart.isBusy = false;
}

ISR(USART3_RX_vect) {
	DebugUsart.rx.insert(UDR3);
}

USART GPSUsart(250, 64);

void initGPSUSART() {
	UBRR0 = 0x0067;
	UCSR0B = (1<<RXEN0) | (1<<RXCIE0) | (1<<TXEN0) | (1<<TXCIE0);
	UCSR0C = (1<<UCSZ00) | (1<<UCSZ01);
	GPSUsart.isBusy = false;
}

ISR(USART0_RX_vect) {
	GPSUsart.rx.insert(UDR0);
}

ISR(USART0_TX_vect) {
	if(!GPSUsart.tx.isEmpty()) UDR0 = GPSUsart.tx.pop();
	else GPSUsart.isBusy = false;
}

void sendGPSUSART() {
	if(GPSUsart.isBusy) return;
	if(!GPSUsart.tx.isEmpty()) {
		GPSUsart.isBusy = true;
		UDR0 = GPSUsart.tx.pop();
	}
}

USART AuxUSART(250, 32);

void initAuxUSART() {
	UBRR1 = 0x0067;
	UCSR1B = (1<<RXEN1) | (1<<RXCIE1) | (1<<TXEN1) | (1<<TXCIE1);
	UCSR1C = (1<<UCSZ10) | (1<<UCSZ11);
	AuxUSART.isBusy = false;
}

ISR(USART1_RX_vect) {
	AuxUSART.rx.insert(UDR1);
}

ISR(USART1_TX_vect) {
	if(!AuxUSART.tx.isEmpty()) UDR1 = AuxUSART.tx.pop();
	else AuxUSART.isBusy = false;
}

void sendAuxUSART() {
	if(AuxUSART.isBusy) return;
	if(!AuxUSART.tx.isEmpty()) {
		AuxUSART.isBusy = true;
		UDR1 = AuxUSART.tx.pop();
	}
}
