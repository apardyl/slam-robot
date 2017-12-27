#include "sonar.h"
#include "usart.h"
#include "time.h"

void sonarRequest() {
	AuxUSART.tx.insert(0x22);
	AuxUSART.tx.insert(0x00);
	AuxUSART.tx.insert(0x00);
	AuxUSART.tx.insert(0x22);
	sendAuxUSART();
}

uint16_t sonarDist = 0;

union IntBuf {
	uint16_t data;
	uint8_t arr[2];
};

void refreshSonar() {
	if (AuxUSART.rx.elementCount() >= 4) {
		IntBuf buf;
		AuxUSART.rx.pop();
		buf.arr[1] = AuxUSART.rx.pop();
		buf.arr[0] = AuxUSART.rx.pop();
		AuxUSART.rx.pop();
		sonarDist = buf.data;
		sonarRequest();
	}
}

uint16_t readSonarBlocking() {
	while (1) {
		if (AuxUSART.rx.elementCount() > 0) {
			AuxUSART.rx.pop();
		}
		sonarRequest();
		uint32_t timeout = milis + 100;
		while(timeout > milis) {
			if (AuxUSART.rx.elementCount() >= 4) {
				IntBuf buf;
				AuxUSART.rx.pop();
				buf.arr[1] = AuxUSART.rx.pop();
				buf.arr[0] = AuxUSART.rx.pop();
				AuxUSART.rx.pop();
				return buf.data;
			}
		}
	}
}
