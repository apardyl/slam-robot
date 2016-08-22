/*
 * encoder.h
 *
 * Created: 2016-08-21 12:27:31
 *  Author: Adam
 */ 


#ifndef ENCODER_H_
#define ENCODER_H_

#include <stdint.h>

extern volatile uint16_t leftEncoder, rightEncoder;
void initEncoders();


#endif /* ENCODER_H_ */