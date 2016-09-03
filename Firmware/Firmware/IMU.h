/* 
* IMU.h
*
* Created: 2016-08-23 17:03:55
* Author: Adam
*/


#ifndef __IMU_H__
#define __IMU_H__

#include <stdint.h>

struct ThreeAxis {
	uint16_t x, y, z;	
};

struct IMU {
	IMU();
	enum states {NONE, SETUP, READ_ACCEL, READ_MAGN};
	volatile ThreeAxis accel, magn;
	states state;
}; //IMU

extern IMU imu;
void imuReceiveAccel(uint8_t * data, uint8_t lenght);
void imuReceiveMagn(uint8_t * data, uint8_t lenght);
void imuWorker();
void imuStart();
void imuStop();

#endif //__IMU_H__
