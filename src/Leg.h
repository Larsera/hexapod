#ifndef Leg_h
#define Leg_h

#include "Arduino.h"

class Leg {
public:
  Leg(float coxaLength, float femusLength, float tibiaLength);
  int update(float newPos[3]);
  float getCoxaAngle();
  float getFemurAngle();
  float getTibiaAngle();
  float* getAngles();
private:
  float coxaLength, femurLength, tibiaLength;
  float coxaAngle, femurAngle, tibiaAngle;
  float offset_z;
  float legLength; // for optimial draft
  float newPos[3];
  float alpha, beta, gamma;
  uint8_t inverted;
};

#endif
