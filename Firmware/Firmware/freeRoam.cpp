#include "freeRoam.h"
#include "motors.h"
#include "sonar.h"
#include "servo.h"
#include "leds.h"
#include "encoder.h"

#define F_CPU 16000000UL
#include <util/delay.h>

#define STOP_DIST 40
#define SPEED 120
#define ROTATE_BY 3500

void freeRoam() {
	while (1) {
		writeLed(0xFF);
		setMotors(SPEED, SPEED);
		_delay_ms(100);
		while (1) {
			uint16_t dist = readSonarBlocking();
			writeLed(dist);
			if (dist < STOP_DIST) {
				break;
			}
			// drive
		}
		setMotors(0, 0);
		_delay_ms(200);
		uint16_t left, right;
		setServo(SERVO0, 0);
		_delay_ms(300);
		right = readSonarBlocking();
		setServo(SERVO0, 180);
		_delay_ms(400);
		left = readSonarBlocking();
		setServo(SERVO0, 90);
		_delay_ms(200);
		
		leftEncoder = 0;
		rightEncoder = 0;
		
		if(left > right) {
			setMotors(-SPEED, SPEED);
		} else {
			setMotors(SPEED, -SPEED);
		}
		
		while (leftEncoder + rightEncoder < ROTATE_BY) {
			// rotate
		}
		setMotors(0, 0);
		//_delay_ms(1000);
	}
}
