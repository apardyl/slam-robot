/*
 * leds.cpp
 *
 * Created: 2016-08-20 13:25:11
 *  Author: Adam
 */ 

#include "leds.h"
#include <avr/io.h>

void initLeds() {
	PORTC = 0x00;
	DDRC = 0xFF;
}

void writeLed(uint8_t data) {
	PORTC = data;
}

void setLed(uint8_t led, bool state) {
	PORTC = (PORTC & ~(1<<led)) | (state << led); 
}

void setLeds(ledColor color) {
	switch(color) {
		case RED:
		PORTC = 0x81;
		break;
		case YELLOW:
		PORTC = 0x42;
		break;
		case GREEN:
		PORTC = 0x24;
		break;
		case BLUE:
		PORTC = 0x18;
		break;
	}
}

void setLights(lightsTypes lights, bool state) {
	switch (lights) {
		case LIGHTS0:
		PORTE = (PORTE & 0xEF) | (state << 4); 
		break;
		case LIGHTS1:
		PORTE = (PORTE & 0xF7) | (state << 3);
		break;
		case LIGHTS2:
		PORTG = (PORTE & 0xDF) | (state << 5);
		break;
	}
}