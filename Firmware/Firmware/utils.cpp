#include "utils.h"
#include <avr/io.h>

#define F_CPU 16000000UL
#include <util/delay.h>


void beep() {
	PORTG |= 0x02;
	_delay_ms(100);
	PORTG &= 0xFD;
}

uint8_t hex2int(const char hex) {
	if(hex >= '0' && hex <= '9') return hex - '0';
	if(hex >= 'A' && hex <= 'F') return hex - 'A' + 10;
	if(hex >= 'a' && hex <= 'f') return hex - 'a' + 10;
	return 0;
}
