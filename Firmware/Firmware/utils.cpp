/*
 * utils.cpp
 *
 * Created: 2016-08-20 13:08:49
 *  Author: Adam
 */ 

#include "utils.h"
#include <avr/io.h>

#define F_CPU 16000000UL
#include <util/delay.h>


void beep() {
	PORTG |= 0x02;
	_delay_ms(100);
	PORTG &= 0xFD;
}