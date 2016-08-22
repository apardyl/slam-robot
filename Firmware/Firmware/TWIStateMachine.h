/* 
* TWIStateMachine.h
*
* Created: 2016-08-22 15:54:00
* Author: Adam
*/


#ifndef __TWISTATEMACHINE_H__
#define __TWISTATEMACHINE_H__

#include <stdint.h>

class TWIStateMachine
{
public:
	TWIStateMachine();
	void init();
	void worker();
	void reset();
	void writeBit(uint8_t addr, uint8_t reg, uint8_t data);
	void readBit(uint8_t addr, uint8_t reg, void (*callback)(uint8_t));
	
private:
	uint8_t address, regAddress;
	volatile uint8_t data;
	void (*readCallback)(uint8_t);
	enum modes {WRITE_REG, READ_REG};
	volatile modes mode;
	
	enum states {NONE, START, SADDR, SREGADR, wSDATA, wSTOP, rRSTART, rRADDR, rRDATA, rSTOP};
	volatile states state;
	
}; //TWIStateMachine

extern TWIStateMachine i2c;

#endif //__TWISTATEMACHINE_H__
