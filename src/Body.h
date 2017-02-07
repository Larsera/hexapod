#ifndef Body_h
#define Body_h

#include "Arduino.h"
#include <Wire.h>
#include "Leg.h"
#include <ServoFlow.h>
#include <Adafruit_PWMServoDriver.h>

#define COXA_LENGTH  13
#define FEMUR_LENGTH 55.5
#define TIBIA_LENGTH 89

class Body {
public:
  Body(Adafruit_PWMServoDriver pwmR, Adafruit_PWMServoDriver pwmL);
  int update();
private:
  Adafruit_PWMServoDriver pwmR, pwmL;
  ServoFlow *sfRight;
  ServoFlow *sfLeft;
  Leg leg[6] = {Leg(COXA_LENGTH, FEMUR_LENGTH, TIBIA_LENGTH, 1), Leg(COXA_LENGTH, FEMUR_LENGTH, TIBIA_LENGTH, 1), Leg(COXA_LENGTH, FEMUR_LENGTH, TIBIA_LENGTH, 1)
    , Leg(COXA_LENGTH, FEMUR_LENGTH, TIBIA_LENGTH, 0), Leg(COXA_LENGTH, FEMUR_LENGTH, TIBIA_LENGTH, 0), Leg(COXA_LENGTH, FEMUR_LENGTH, TIBIA_LENGTH, 0)};
};

#endif
