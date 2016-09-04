/*
 * Firmware.cpp
 *
 * Created: 2016-08-20 13:05:51
 * Author : Adam
 */ 

#include "power.h"
#include "utils.h"
#include "leds.h"
#include "motors.h"
#include "servo.h"
#include "encoder.h"
#include "usart.h"
#include "TWIStateMachine.h"
#include "IMU.h"
#include "time.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdio.h>

void initPorts() {
	PORTB = 0x00;
	DDRB =  0xF0;
	
	PORTC = 0x00;
	DDRC = 0xFF;
	
	PORTD = 0x00;
	DDRD = 0x30;
	
	PORTE = 0x00;
	DDRE = 0x18;
	
	PORTG = 0x00;
	DDRG = 0x22;
	
	PORTH = 0x00;
	DDRH = 0x7C;
	
	PORTL = 0x02;
	DDRL = 0xFF;
}

void test(uint8_t data) {
	uint8_t lol = data;
	writeLed(lol);
}

int main(void) {
	initTime();
	initPorts();
	initPower();
	initLeds();
	initDebugUSART();
	initGPSUSART();
	initMotors();
	initServos();
	initEncoders();
	i2c.init();
	imuStart();

	beep();
	
	sei();
	
	_delay_ms(1000);
	
	DebugUsart.tx.insertString("\r\n#### START ####\r\n");
	sendDebugUSART();
	
	//_delay_ms(1000);
	
	//volatile bool lol = true;
	
	while (1) {
		imuWorker();
		
		moveLine(GPSUsart.rx, DebugUsart.tx);
//		if(!GPSUsart.rx.isEmpty()) DebugUsart.tx.insert(GPSUsart.rx.pop());
		
		static uint32_t last;
		if(milis - last > 200) {
			last = milis;
			static char data[25];		
			sprintf(data, "$ACCE,%04X,%04X,%04X\r\n", imu.accel.x, imu.accel.y, imu.accel.z);
			DebugUsart.tx.insertString(data);
			sprintf(data, "$MAGN,%04X,%04X,%04X\r\n", imu.magn.x, imu.magn.y, imu.magn.z);
			DebugUsart.tx.insertString(data);
			sprintf(data, "$GYRO,%04X,%04X,%04X\r\n", imu.gyro.x, imu.gyro.y, imu.gyro.z);
			DebugUsart.tx.insertString(data);
			sprintf(data, "$ENCO,%04X,%04X\r\n", leftEncoder, rightEncoder);
			DebugUsart.tx.insertString(data);
		}
		//if(lol) DebugUsart.tx.insertString("\r\n1234567890 START 1234567890\r\n");
		sendDebugUSART();
	}
}