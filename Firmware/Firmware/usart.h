/*
 * usart.h
 *
 * Created: 2016-08-20 22:12:35
 *  Author: Adam
 */ 


#ifndef USART_H_
#define USART_H_

#include "FIFO.h"

struct USART {
	FIFO rx, tx;
	bool isBusy;
	USART(uint8_t RXbuff, uint8_t TXbuff) : isBusy(true), rx(RXbuff), tx(TXbuff) {}
};

void initDebugUSART();
extern USART DebugUsart;
void sendDebugUSART();

void initGPSUSART();
extern USART GPSUsart;
void sendGPSUSART();

#endif /* USART_H_ */