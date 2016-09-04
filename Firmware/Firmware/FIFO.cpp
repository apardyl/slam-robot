/* 
* FIFO.cpp
*
* Created: 2016-08-21 16:52:36
* Author: Adam
*/


#include "FIFO.h"
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>

FIFO::FIFO(uint8_t lenght) : head(0), tail(0), count(0), size(lenght), lines(0) {
	buffer = (uint8_t*)calloc(lenght, sizeof(uint8_t));
}

FIFO::~FIFO() {
	free((void*)buffer);
}

bool FIFO::isEmpty() {
	return count == 0;
}

bool FIFO::isFULL() {
	return count == size;
}

uint8_t FIFO::elementCount() {
	return count;
}

uint8_t FIFO::linesInBufffer() {
	return lines;
}

void FIFO::insert(uint8_t data) {
	if(isFULL()) return;
	*(buffer + head) = data;
	uint8_t sreg = SREG; cli();
	head += 1;
	if(head >= size) head = 0;
	count += 1;
	if(data == '\n') lines += 1;
	SREG = sreg;
}

uint8_t FIFO::pop() {
	uint8_t x = *(buffer + tail);
	uint8_t sreg = SREG; cli();
	count -= 1;
	tail += 1;
	if(tail >= size) tail = 0;
	if(x == '\n') lines -= 1;
	SREG = sreg;
	return x;
}

void FIFO::insertString(const char * string) {
	for(int i = 0;; i++) {
		if(string[i] == '\0') break;
		insert(string[i]);
	}
}

void moveLine(FIFO& a, FIFO& b) {
	if(a.linesInBufffer() == 0) return;
	
	uint8_t c;
	
	do {
		c = a.pop();
		b.insert(c);
	} while(c!='\n');
}