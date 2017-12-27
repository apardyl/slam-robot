#ifndef USART_H_
#define USART_H_

#include "FIFO.h"

struct USART {
	FIFO rx, tx;
	bool isBusy;
	USART(uint8_t RXbuff, uint8_t TXbuff) : rx(RXbuff), tx(TXbuff), isBusy(true) {}
};

void initDebugUSART();
extern USART DebugUsart;
void sendDebugUSART();

void initGPSUSART();
extern USART GPSUsart;
void sendGPSUSART();

#endif /* USART_H_ */