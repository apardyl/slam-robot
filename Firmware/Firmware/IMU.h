#ifndef __IMU_H__
#define __IMU_H__

#include <stdint.h>

struct ThreeAxis {
	uint16_t x, y, z;
};

class IMU {
public:	
	volatile ThreeAxis accel, magn, gyro;
	void receiveAccel(uint8_t * data, uint8_t lenght);
	void receiveMagn(uint8_t * data, uint8_t lenght);
	void receiveGyro(uint8_t * data, uint8_t lenght);
	void worker();
	void start();
	void stop();
	IMU() : state(NONE) {}
private:
	enum states : uint8_t {NONE, SETUP_LSM303D, SETUP_L3GD20H, READ_ACCEL, READ_MAGN, READ_GYRO, WAIT};
	uint32_t last;
	states state;
};

extern IMU imu;

#endif //__IMU_H__
