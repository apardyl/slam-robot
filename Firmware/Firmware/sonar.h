#ifndef SONAR_H_
#define SONAR_H_

#include <stdint.h>

uint16_t readSonarBlocking();

void refreshSonar();

void sonarRequest();

extern uint16_t sonarDist;

#endif /* SONAR_H_ */
