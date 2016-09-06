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
#include "i2c.h"
#include "IMU.h"
#include "time.h"
#include "ADC.h"

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
	imu.start();
	adc.start();
	
	
	beep();
	_delay_ms(100);
	
	sei();
		
	DebugUsart.tx.insertString("\r\n#### START ####\r\n");
	sendDebugUSART();
	
	while (1) {
		imu.worker();
		
		moveLine(GPSUsart.rx, DebugUsart.tx);
		
		static uint32_t last;
		if(milis - last > 200) {
			last = milis;
			static char data[30];		
			sprintf(data, "$ACCE,%04X,%04X,%04X\r\n", imu.accel.x, imu.accel.y, imu.accel.z);
			DebugUsart.tx.insertString(data);
			sprintf(data, "$MAGN,%04X,%04X,%04X\r\n", imu.magn.x, imu.magn.y, imu.magn.z);
			DebugUsart.tx.insertString(data);
			sprintf(data, "$GYRO,%04X,%04X,%04X\r\n", imu.gyro.x, imu.gyro.y, imu.gyro.z);
			DebugUsart.tx.insertString(data);
			sprintf(data, "$ENCO,%04X,%04X\r\n", leftEncoder, rightEncoder);
			DebugUsart.tx.insertString(data);
			sprintf(data, "$BATT,%04X,%04X,%04X,%04X\r\n", adc.read(adc.ADC11), adc.read(adc.ADC10), adc.read(adc.ADC9), adc.read(adc.ADC8));
			DebugUsart.tx.insertString(data);
		}
		sendDebugUSART();
	}
}