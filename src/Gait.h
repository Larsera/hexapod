#ifndef Gait_h
#define Gait_h

#include "Arduino.h"

#define OFFSET_X 100
#define OFFSET_Y -50
#define OFFSET_Z 50

class Gait {
public:
  Gait();
  void animate();
  float* getR1();
private:
  float movVec[3] = {0};
  float animSteps[3*3] = {OFFSET_X, OFFSET_Y - 50,  OFFSET_Z + 100,
                          OFFSET_X, OFFSET_Y + 75, OFFSET_Z - 25,
                          OFFSET_X, OFFSET_Y + 150, OFFSET_Z + 100};
  float r1Pos[3] = {OFFSET_X, OFFSET_Y, OFFSET_Z};
  float r2Pos[3] = {OFFSET_X, OFFSET_Y, OFFSET_Z};
  float r3Pos[3] = {OFFSET_X, OFFSET_Y, OFFSET_Z};
  float l1Pos[3] = {OFFSET_X, OFFSET_Y, OFFSET_Z};
  float l2Pos[3] = {OFFSET_X, OFFSET_Y, OFFSET_Z};
  float l3Pos[3] = {OFFSET_X, OFFSET_Y, OFFSET_Z};

  float legs[6][3] = {{OFFSET_X, OFFSET_Y, OFFSET_Z},
   {OFFSET_X, OFFSET_Y, OFFSET_Z},
   {OFFSET_X, OFFSET_Y, OFFSET_Z},
   {OFFSET_X, OFFSET_Y, OFFSET_Z},
   {OFFSET_X, OFFSET_Y, OFFSET_Z},
   {OFFSET_X, OFFSET_Y, OFFSET_Z}};

  uint32_t lastTime = millis();
  int currentAnimStep = 0;
  float getNextAnimStep();
};

#endif
