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

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>

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
	initPorts();
	initPower();
	initLeds();
	setLeds(RED);
	initDebugUSART();
	initGPSUSART();
	initMotors();
	initServos();
	initEncoders();
	i2c.init();
	imu.start();

	beep();
	
	sei();
	
	//_delay_ms(1000);
	//i2c.write(0x1D,0x24,0xF0);
	imu.worker();
	_delay_ms(1000);	

	i2c.read(0x1D,0x20,test);	
	
	for(int i = 0; i<25; i++) {
		FIFOTxDebugUsart.insert('#');
	}
	FIFOTxDebugUsart.insert('\n');
	sendDebugUSART();
	
	while (1) {
		if(!FIFORxGPSUsart.isEmpty()) FIFOTxDebugUsart.insert(FIFORxGPSUsart.pop());
		sendDebugUSART();
	}
}