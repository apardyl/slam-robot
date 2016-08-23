/* 
* TWIStateMachine.cpp
*
* Created: 2016-08-22 15:54:00
* Author: Adam
*/


#include "TWIStateMachine.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdlib.h>

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

void TWIStateMachine::read(uint8_t addr, uint8_t reg, void (*callback)(uint8_t)) {
	if(state != NONE) return;
	address = addr;
	regAddress = reg;
	arrayLenght = 1;
	counter = 0;
	readCallback = callback;
	dataArray = (volatile uint8_t*)malloc(1);
	mode = READ_REG;
	state = START;
	worker();
}

void TWIStateMachine::read(uint8_t addr, uint8_t reg, void (*callback)(uint8_t *, uint8_t), uint8_t lenght) {
	if(state != NONE) return;
	address = addr;
	regAddress = reg;
	arrayLenght = lenght;
	counter = 0;
	readCallbackArray = callback;
	dataArray = (volatile uint8_t*)malloc(lenght);
	mode = READ_REG;
	state = START;
	worker();
}

void TWIStateMachine::write(uint8_t addr, uint8_t reg, uint8_t dataToWrite) {
	if(state != NONE) return;
	address = addr;
	regAddress = reg;
	arrayLenght = 1;
	counter = 0;
	dataArray = &dataToWrite;
	mode = WRITE_REG;
	state = START;
	worker();
}

void TWIStateMachine::write(uint8_t addr, uint8_t reg, uint8_t * dataArrayToWrite, uint8_t lenght) {
	if(state != NONE) return;
	address = addr;
	regAddress = reg;
	arrayLenght = lenght;
	dataArray = dataArrayToWrite;
	counter = 0;
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
			TWDR = *(dataArray + counter);
			TWCR = ( 1 << TWEN ) | (1 << TWIE) | (1 << TWINT);
			counter++;
			state = (counter == arrayLenght) ? wSTOP : wSDATA;
			break;
		case wSTOP:
			TWCR = ( 1 << TWEN ) | (1 << TWIE) | (1 << TWINT) | (1 << TWSTO);
			state = NONE;
			break;
		case rRSTART:
			TWCR = ( 1 << TWEN ) | (1 << TWIE) | (1 << TWSTA) | (1 << TWINT);
			state = rRADDR;
			break;
		case rRADDR:
			TWDR = (address << 1) | 0x01;
			TWCR = ( 1 << TWEN ) | (1 << TWIE) | (1 << TWINT);
			state = (arrayLenght == 1) ? rRDATA : rRDATAFIRST;
			break;
		case rRDATA:
			TWCR = ( 1 << TWEN ) | (1 << TWIE) | (1 << TWINT);
			state = rSTOP;
			break;
		case rRDATAFIRST:
			TWCR = ( 1 << TWEN ) | (1 << TWIE) | (1 << TWINT) | (1 << TWEA);
			state = (arrayLenght == 2) ? rRDATALAST : rRDATAMIDDLE;
			break;
		case rRDATAMIDDLE:
			*(dataArray + counter) = TWDR;
			TWCR = ( 1 << TWEN ) | (1 << TWIE) | (1 << TWINT) | (1 << TWEA);
			counter++;
			state = (counter + 2 == arrayLenght) ? rRDATALAST : rRDATAMIDDLE;
			break;
		case rRDATALAST:
			*(dataArray + counter) = TWDR;
			TWCR = ( 1 << TWEN ) | (1 << TWIE) | (1 << TWINT);
			counter++;
			state = rSTOP;
		case rSTOP:
			*(dataArray + counter) = TWDR;
			TWCR = ( 1 << TWEN ) | (1 << TWIE) | (1 << TWINT) | (1 << TWSTO);
			state = NONE;
			if(arrayLenght == 1) readCallback(*dataArray);
			else readCallbackArray((uint8_t*)dataArray, arrayLenght);
			break;
	}
}

TWIStateMachine i2c;

ISR(TWI_vect) {
	i2c.worker();
}
