/*
 * ADC.h
 *
 * Created: 2016-09-05 13:02:13
 *  Author: Adam
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

class Adc {
public:
	void worker();
	enum ports : uint8_t {ADC0 = 0, ADC1, ADC2, ADC3, ADC8 = 8, ADC9, ADC10, ADC11, ADC12, ADC13, ADC14, ADC15};
	uint16_t read(ports port);
	void isr();
	Adc() : isBusy(false), current(ADC0) {}
	bool isBusy;
private:
	volatile ports current;
	volatile uint16_t reading[16];
};

extern Adc adc;

#endif /* ADC_H_ */