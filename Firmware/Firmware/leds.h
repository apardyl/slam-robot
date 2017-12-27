#ifndef LEDS_H_
#define LEDS_H_

#include <stdint.h>

void initLeds();
void writeLed(uint8_t data);
void setLed(uint8_t led, bool state);

enum ledColor {RED, YELLOW, GREEN, BLUE};
void setLeds(ledColor color);

enum lightsTypes {LIGHTS0, LIGHTS1, LIGHTS2};
void setLights(lightsTypes lights, bool state);

#endif /* LEDS_H_ */
