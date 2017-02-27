#ifndef Leg_h
#define Leg_h

#include "Arduino.h"

#define LEG_PI 3.14159265359

class Leg {
public:
  Leg(float coxaLength, float femusLength, float tibiaLength, uint8_t inverted);
  int update(float newPos[3]);
  float getCoxaAngle();
  float getFemurAngle();
  float getTibiaAngle();
  float* getAngles();
private:
  float coxaLength, femurLength, tibiaLength;
  float coxaLength2, femurLength2, tibiaLength2;
  float coxaAngle, femurAngle, tibiaAngle;
  // float legLength; // for optimial draft
  float newPos[3];
  float oldPos[3];
  uint8_t inverted;
};

#endif
