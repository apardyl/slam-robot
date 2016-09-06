/*
 * ADC.cpp
 *
 * Created: 2016-09-05 13:35:36
 *  Author: Adam
 */ 

#include "ADC.h"
#include <avr/io.h>
#include <avr/interrupt.h>
	
Adc adc;
	
void Adc::start() {
	ADMUX = (1<<REFS0);
	ADCSRA = (1<<ADEN) | (1<<ADSC) | (1<<ADIE) | (1<<ADPS2) | (1<<ADPS1);
}

void Adc::stop() {
	ADCSRA = 0x00;
}

uint16_t Adc::read(ports port) {
	return reading[port];
}

void Adc::worker() {
	reading[current] = ADC;
	if(current == ADC3) current = ADC8;
	else if(current == ADC15) current = ADC0;
	else current = (ports)(((uint8_t)current) + 1);
	
	ADMUX = (1<<REFS0) | (current & 0b111);
	ADCSRB = current & 0b1000;
	ADCSRA = (1<<ADEN) | (1<<ADSC) | (1<<ADIE) | (1<<ADPS2) | (1<<ADPS1);
}
	

ISR(ADC_vect) {
	adc.worker();
}