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
	void write(const uint8_t addr, const uint8_t reg, const uint8_t dataToWrite);
	void write(const uint8_t addr, const uint8_t reg, const uint8_t * dataArrayToWrite, const uint8_t lenght);
	void read(const uint8_t addr, const uint8_t reg, void (*callback)(uint8_t));
	void read(const uint8_t addr, const uint8_t reg, void (*callback)(uint8_t *, uint8_t), uint8_t lenght);
	bool isBusy();
private:
	uint8_t address, regAddress;
	volatile uint8_t * dataArray;
	volatile uint8_t arrayLenght;
	volatile uint8_t counter;
	void (*readCallback)(uint8_t);
	void (*readCallbackArray)(uint8_t *, uint8_t);
	enum modes {WRITE_REG, READ_REG};
	volatile modes mode;
	
	enum states {NONE, START, SADDR, SREGADR, wSDATA, wSTOP, rRSTART, rRADDR, rRDATA, rRDATAFIRST, rRDATAMIDDLE, rRDATALAST, rSTOP};
	volatile states state;
	
}; //TWIStateMachine

extern TWIStateMachine i2c;

#endif //__TWISTATEMACHINE_H__
