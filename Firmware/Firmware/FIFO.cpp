/* 
* FIFO.cpp
*
* Created: 2016-08-21 16:52:36
* Author: Adam
*/


#include "FIFO.h"
#include <stdlib.h>


FIFO::FIFO(uint8_t lenght) : head(0), tail(0), count(0), size(lenght) {
	buffer = (uint8_t*)malloc(lenght);
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

void FIFO::insert(uint8_t data) {
	if(isFULL()) return;	
	*(buffer + this->head) = data;
	head++;
	head = (head < size) ? head : 0;
	count++;
}

uint8_t FIFO::pop() {
	if(isEmpty()) return 0x00;
	uint8_t x = *(buffer + tail);
	tail++;
	tail = (tail < size) ? tail : 0;
	count--;
	return x;
}