/*
 * usart.h
 *
 * Created: 2016-08-20 22:12:35
 *  Author: Adam
 */ 


#ifndef USART_H_
#define USART_H_

#include "FIFO.h"

void initDebugUSART();
extern FIFO FIFOTxDebugUsart;
extern FIFO FIFORxDebugUsart;
void sendDebugUSART();

void initGPSUSART();
extern FIFO FIFORxGPSUsart;

#endif /* USART_H_ */