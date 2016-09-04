/* 
* FIFO.h
*
* Created: 2016-08-21 16:52:36
* Author: Adam
*/


#ifndef __FIFO_H__
#define __FIFO_H__

#include <stdint.h>

class FIFO {
public:
	FIFO(uint8_t lenght);
	~FIFO();
	void insert(uint8_t data);
	void insertString(const char * string);
	uint8_t pop();
	uint8_t linesInBufffer();
	bool isFULL();
	bool isEmpty();
	uint8_t elementCount();
private:
	volatile uint8_t * buffer;
	volatile uint8_t head, tail, count, size, lines;
}; //FIFO

void moveLine(FIFO& a, FIFO& b);

#endif //__FIFO_H__
