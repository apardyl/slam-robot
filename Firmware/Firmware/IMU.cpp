/* 
* IMU.cpp
*
* Created: 2016-08-23 17:03:55
* Author: Adam
*/


#include "IMU.h"
#include "TWIStateMachine.h"

#define LSM303D 0x1D
#define L3GD20H 0x6B
#define MULTIBYTE 7

IMU::IMU() : state(NONE) {
}

void imuStart() {
	imu.state = imu.SETUP_LSM303D;
}

void imuStop() {
	imu.state = imu.NONE;
}

void imuWorker() {
	if(i2c.isBusy()) return;

	switch (imu.state) {
		case imu.NONE:
			break;
		case imu.SETUP_LSM303D: {
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
			i2c.write(LSM303D, 0x1F | (1<<MULTIBYTE), config, 8);	
			imu.state = imu.SETUP_L3GD20H;
			break;
		}
		case imu.SETUP_L3GD20H: {
			const uint8_t config[5] = {
				0x6F, //200 Hz ODR, 50 Hz bandwidth, enable all
				0x00, //no triger, no high-pass
				0x00, //no int
				0x00, //no block, lsp first, 245dps, no level sensitive latched, no self-test
				0x00, //no reboot, no fifo, no high-pass, no int
			};
			i2c.write(L3GD20H, 0x20 | (1<<MULTIBYTE), config, 6);
			imu.state = imu.READ_ACCEL;
			break;
		}
		case imu.READ_ACCEL:
			i2c.read(LSM303D, 0x28 | (1<<MULTIBYTE), imuReceiveAccel, 6);
			imu.state = imu.READ_MAGN;
			break;
		case imu.READ_MAGN:
			i2c.read(LSM303D, 0x08 | (1<<MULTIBYTE), imuReceiveMagn, 6);
			imu.state = imu.READ_GYRO;
			break;
		case  imu.READ_GYRO:
			i2c.read(L3GD20H, 0x28 | (1<<MULTIBYTE), imuReceiveGyro, 6);
			imu.state = imu.READ_ACCEL;
			break; 
	}
}

IMU imu;

void imuReceiveAccel(uint8_t * data, uint8_t lenght) {
	imu.accel.x = ((uint16_t)data[1])<<8 | data[0];
	imu.accel.y = ((uint16_t)data[3])<<8 | data[2];
	imu.accel.z = ((uint16_t)data[5])<<8 | data[4];
}

void imuReceiveMagn(uint8_t * data, uint8_t lenght) {
	imu.magn.x = ((uint16_t)data[1])<<8 | data[0];
	imu.magn.y = ((uint16_t)data[3])<<8 | data[2];
	imu.magn.z = ((uint16_t)data[5])<<8 | data[4];
}

void imuReceiveGyro(uint8_t * data, uint8_t lenght) {
	imu.gyro.x = ((uint16_t)data[1])<<8 | data[0];
	imu.gyro.y = ((uint16_t)data[3])<<8 | data[2];
	imu.gyro.z = ((uint16_t)data[5])<<8 | data[4];
}
