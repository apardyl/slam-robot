#ifndef SERVOS_H_
#define SERVOS_H_

#include <stdint.h>

void initServos();

enum servoTypes {SERVO0, SERVO1, SERVO2};

void setServo(servoTypes servo, uint16_t value);
void stopServo(servoTypes servo);


#endif /* SERVOS_H_ */
