/* 
* IMU.cpp
*
* Created: 2016-08-23 17:03:55
* Author: Adam
*/


#include "IMU.h"
#include "TWIStateMachine.h"

IMU::IMU() : state(NONE) {
}

void IMU::start() {
	state = SETUP;
}

void IMU::stop() {
	state = NONE;
}

void IMU::worker() {
	if(i2c.isBusy()) return;

	switch (state) {
		case NONE:
			break;
		case SETUP:
			const uint8_t config[8] = {
				0x00, //no fifo
				0x57, //50hz, xyz on
				0x00, //+/-2G
				0x00, //no int
				0x00, //no int
				0xF0, //temp sensor enabled, max res magn, 50Hz, no int
				0x00, //+/-2gauss
				0x00 //no filter, no low power mode
			};
			i2c.write(LSM303D, 0x1F | (1<<7), config, 8);	
			state = NONE;
			break;
	}
}

IMU imu;