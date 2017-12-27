#include "motors.h"
#include <avr/io.h>

#define MAXSAFESPEED 0xFF

void initMotors() {
	OCR5B = 0x00;
	OCR5C = 0x00;
	TCCR5A = (1<<WGM50) | (1<<COM5B1) | (1<<COM5C1);
	TCCR5B = (1<<CS51);
}

void setMotors(uint8_t left, uint8_t right) {	
	if(left == 0) {
		PORTL &= 0x1F;
	} else if(left < 0x80) {
		PORTL = (PORTL | 0xA0) & 0xBF;
	} else {
		PORTL = (PORTL | 0x60) & 0x7F;
	}
	
	if(right == 0) {
		PORTL &= 0xE3;
	} else if(right > 0x80) {
		PORTL = (PORTL | 0x14) & 0xF7;
	} else {
		PORTL = (PORTL | 0x18) & 0xFB;
	}
	
	left<<=1; right<<=1;
	OCR5B = (right > MAXSAFESPEED) ? MAXSAFESPEED : right;
	OCR5C = (left > MAXSAFESPEED) ? MAXSAFESPEED : left;
}
