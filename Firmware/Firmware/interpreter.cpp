#include "interpreter.h"
#include <stdio.h>
#include "power.h"
#include "motors.h"
#include "utils.h"


void interpreter(FIFO& fifo) {
	while(fifo.front() != '#' && fifo.linesInBufffer() > 0) fifo.pop();
	if(fifo.linesInBufffer() == 0) return;
	fifo.pop();
	
	uint8_t data[16];
	for(uint8_t i = 0; i<16 && fifo.front() != '\n' && fifo.front() != '\r'; i++) data[i] = fifo.pop();
	while(fifo.front() == '\n' || fifo.front() == '\r') fifo.pop();
	
	switch(data[0]) {
		case 'M': //Motors
			switch(data[1]) {
				case 'E':
					enableMotors(true);
					break;
				case 'D':
					enableMotors(false);
					break;
				case 'B':
					setMotors(0, 0);
					break;
				case 'S':
					setMotors((hex2int(data[3])<<4) | hex2int(data[4]), (hex2int(data[6])<<4) | hex2int(data[7]));
					break;
			}
			break;
	}
}
