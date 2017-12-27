#include "servo.h"
#include <avr/io.h>


void initServos() {
	OCR4A = 0x00;
	OCR4B = 0x00;
	OCR4C = 0x00;
	
	TCCR4A = (1<<COM4A1) | (1<<COM4B1) | (1<<COM4C1) | (1<<WGM41);
	TCCR4B = (1<<WGM42) | (1<<WGM43) | (1<<CS41) | (1<<CS40);
	ICR4=4999;
	DDRH |= (1<<PH3) | (1<<PH4) | (1<<PH5);
}


void setServo(servoTypes servo, uint16_t value) {
	if (value > 180) {
		return;
	}
	
	value = int((float(value) * 2.7) + 120);
	switch (servo) {
		case SERVO0:
			OCR4A = value;
			break;
		case SERVO1:
			OCR4B = value;
			break;
		case SERVO2:
			OCR4C = value;
			break;
	}
}

void stopServo(servoTypes servo) {
	switch (servo) {
		case SERVO0:
			OCR4A = 0;
			break;
		case SERVO1:
			OCR4B = 0;
			break;
		case SERVO2:
			OCR4C = 0;
			break;
	}
}
