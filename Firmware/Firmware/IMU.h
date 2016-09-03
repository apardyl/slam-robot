/* 
* IMU.h
*
* Created: 2016-08-23 17:03:55
* Author: Adam
*/


#ifndef __IMU_H__
#define __IMU_H__

#define LSM303D 0x1D

class IMU
{
public:
	IMU();
	void worker();
	void start();
	void stop();
	enum states {NONE, SETUP};
	states state;
private:

}; //IMU

extern IMU imu;

#endif //__IMU_H__
