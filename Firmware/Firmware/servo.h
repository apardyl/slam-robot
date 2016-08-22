/*
 * servos.h
 *
 * Created: 2016-08-20 17:51:24
 *  Author: Adam
 */ 


#ifndef SERVOS_H_
#define SERVOS_H_

#include <stdint.h>

void initServos();

enum servoTypes {SERVO0, SERVO1, SERVO3};

void setServo(servoTypes servo, uint8_t value);


#endif /* SERVOS_H_ */