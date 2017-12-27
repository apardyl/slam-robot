#include "servo.h"
#include <avr/io.h>


void initServos() {
	OCR4A = 0x00;
	OCR4B = 0x00;
	OCR4C = 0x00;
	
	TCCR4A = (1<<COM4A1) | (1<<COM4B1) | (1<<COM4C1) | (1<<WGM41);
	TCCR4B = (1<<WGM42) | (1<<WGM43) | (1<<CS41) | (1<<CS40);
	ICR4=4999;
}