/* 
* TWIStateMachine.cpp
*
* Created: 2016-08-22 15:54:00
* Author: Adam
*/


#include "TWIStateMachine.h"
#include <avr/interrupt.h>
#include <avr/io.h>

TWIStateMachine::TWIStateMachine() : state(NONE) {
}

void TWIStateMachine::init() {
	TWBR = 0x48; //100kHz
	TWSR &= ~((1<<TWPS0) | (1<<TWPS1));
	TWCR = (1<<TWEN);
}

void TWIStateMachine::reset() {
	state = NONE;
	TWCR = 0x00;
}

void TWIStateMachine::readBit(uint8_t addr, uint8_t reg, void (*callback)(uint8_t)) {
	if(state != NONE) return;
	address = addr;
	regAddress = reg;
	readCallback = callback;
	mode = READ_REG;
	state = START;
	worker();
}

void TWIStateMachine::writeBit(uint8_t addr, uint8_t reg, uint8_t data) {
	if(state != NONE) return;
	address = addr;
	regAddress = reg;
	mode = WRITE_REG;
	state = START;
	worker();
}

void TWIStateMachine::worker() {
	switch (state) {
		case NONE:
			break;
		case START:
			TWCR = ( 1 << TWEN ) | (1 << TWIE) | (1 << TWSTA) | (1<< TWINT);
			state = SADDR;
			break;
		case SADDR:
			TWDR = address<<1;
			TWCR = ( 1 << TWEN ) | (1 << TWIE) | (1<< TWINT);
			state = SREGADR;
			break;
		case SREGADR:
			TWDR = regAddress;
			TWCR = ( 1 << TWEN ) | (1 << TWIE) | (1<< TWINT);
			state = (mode == WRITE_REG) ? wSDATA : rRSTART;
			break;
		case wSDATA:
			TWDR = data;
			TWCR = ( 1 << TWEN ) | (1 << TWIE) | (1 << TWINT);
			state = wSTOP;
			break;
		case wSTOP:
			TWCR = ( 1 << TWEN ) | (1 << TWIE) | (1 << TWINT) | (1 << TWSTO);
			state = NONE;
			break;
		case rRSTART:
			TWCR = ( 1 << TWEN ) | (1 << TWIE) | (1 << TWSTA) | (1<< TWINT);
			state = rRADDR;
			break;
		case rRADDR:
			TWDR = (address<<1) | 0x01;
			TWCR = ( 1 << TWEN ) | (1 << TWIE) | (1<< TWINT);
			state = rRDATA;
			break;
		case rRDATA:
			TWCR = ( 1 << TWEN ) | (1 << TWIE) | (1 << TWINT);
			state = rSTOP;
			break;
		case rSTOP:
			data = TWDR;
			TWCR = ( 1 << TWEN ) | (1 << TWIE) | (1 << TWINT) | (1 << TWSTO);
			state = NONE;
			readCallback(data);
			break;
	}
}

TWIStateMachine i2c;

ISR(TWI_vect) {
	i2c.worker();
}
