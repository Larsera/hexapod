#ifndef Leg_h
#define Leg_h

#include "Arduino.h"

class Leg {
public:
  Leg(uint16_t limits[6], uint16_t lengths[3], uint8_t inverted);
  int update();
private:
  float coxa, femur, tibia;
  float legLength;
  float newPos[3];
  uint8_t inverted;
};

#endif
