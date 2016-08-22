/*
 * encoder.cpp
 *
 * Created: 2016-08-21 12:28:39
 *  Author: Adam
 */ 

#include "encoder.h"
#include <avr/interrupt.h>
#include <avr/io.h>

volatile uint16_t leftEncoder = 0, rightEncoder = 0;

void initEncoders() {
	DDRE &= ~((1<<PE5) | (1<<PE6));
	PORTE &= ~((1<<PE5) | (1<<PE6));
	EICRB |= (1<<ISC50) | (1<<ISC60);
	EIMSK |= (1<<INT5) | (1<<INT6);
}

ISR(INT5_vect) {
	leftEncoder++;
}

ISR(INT6_vect) {
	rightEncoder++;
}