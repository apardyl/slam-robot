/*
 * power.cpp
 *
 * Created: 2016-08-20 13:09:53
 *  Author: Adam
 */ 

#include "power.h"
#include <avr/io.h>

void initPower() {
	PORTD &= ~((1<<PD4) | (1<<PD5));
	DDRD |= ((1<<PD4) | (1<<PD5));
	PORTL = (PORTL & ~(1<<PL0)) | (1<<PL1);
	DDRL |= ((1<<PL0) | (1<<PL1));
	PORTH &= ~(1<<PH2);
	DDRH |= (1<<PH2);
}

void enableCPU(bool enable) {
	PORTD = (PORTD & ~(1<<PD4)) | (enable<<PD4);
}

void enableKinect(bool enable) {
	PORTD = (PORTD & ~(1<<PD5)) | (enable<<PD5);
}

void enableServos(bool enable) {
	PORTL = (PORTL & ~(1<<PL0)) | (enable<<PL0);
}

void enableMotors(bool enable) {
	PORTL = (PORTL & ~(1<<PL1)) | ((~enable)<<PL1);
}

void enableAudio(bool enable) {
	PORTH = (PORTH & ~(1<<PH2)) | (enable<<PH2);
}