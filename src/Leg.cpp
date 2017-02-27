#include "Leg.h"
#include <MemoryFree.h>

Leg::Leg(float coxaLength, float femurLength, float tibiaLength, uint8_t inverted) {
this->coxaLength = coxaLength;
this->femurLength = femurLength;
this->tibiaLength = tibiaLength;
this->inverted = inverted;

this->coxaLength2 = pow(coxaLength, 2);
this->femurLength2 = pow(femurLength, 2);
this->tibiaLength2 = pow(tibiaLength, 2);
}

float Leg::getCoxaAngle() {
  return this->coxaAngle;
}

float Leg::getFemurAngle() {
  return this->femurAngle;
}

float Leg::getTibiaAngle() {
  return this->tibiaAngle;
}

float* Leg::getAngles() {
  float angles[3] = {this->coxaAngle, this->femurAngle, this->tibiaAngle};
  return angles;
}

int Leg::update(float newPos[3]) {
  if((newPos[0] == oldPos[0] && newPos[1] == oldPos[1] && newPos[2] == oldPos[2])) {
    return 1;
  }
  
  float gamma = atan2(newPos[0], newPos[1]);

  float l1 = sqrt(pow(newPos[0], 2) + pow(newPos[1], 2));
  // Optimize by sqrt(x)^2 = x
  float l = sqrt(pow(newPos[2], 2) + pow(l1 - this->coxaLength, 2));

  float a1 = acos(newPos[2]/l);
  float a2 = acos((this->tibiaLength2 - this->femurLength2 - pow(l, 2)) / (-2 * this->femurLength * l));
  float alpha = a1 + a2;

  float beta = acos((pow(l, 2) - this->tibiaLength2 - this->femurLength2) / (-2 * this->tibiaLength * this->femurLength));

  if (!inverted){
    this->femurAngle = 180 + -alpha * 180/LEG_PI;
    this->tibiaAngle =        beta  * 180/LEG_PI;
    this->coxaAngle  =        gamma * 180/LEG_PI;
  } else {
    this->femurAngle =        alpha * 180/LEG_PI;
    this->tibiaAngle = 180 + -beta  * 180/LEG_PI;
    this->coxaAngle  = 180 + -gamma * 180/LEG_PI;
  }

  this->oldPos[0] = newPos[0];
  this->oldPos[1] = newPos[1];
  this->oldPos[2] = newPos[2];

  return 0;
}
/*
int Leg::update(float newPos[3]) {
  float pi = 3.14159265359;
  this->legLength = sqrt(pow(newPos[0], 2) + pow(newPos[2], 2));
  float HF = sqrt(pow(legLength - this->coxaLength, 2) + pow(newPos[1], 2));
  float a1 = atan2(legLength - this->coxaLength, newPos[1]);
  float a2 = acos(((pow(this->femurLength, 2) - pow(this->tibiaLength, 2)) + pow(HF, 2)) / (2 * this->femurLength * HF));
  this->femurAngle = 180 + (-(a1 + a2) * 180 / pi + 90);

  float b1 = -( 90 - (((acos((pow(this->femurLength, 2) + pow(this->tibiaLength, 2) - pow(HF, 2)) / (2 * this->femurLength * this->tibiaLength))) * 180) / pi));
  this->tibiaAngle = 90 + b1;

  this->coxaAngle = 90 + atan2(newPos[2], newPos[0]) * 180 / pi;

  return 0;
}

// ANGLES ARE CALCULATED
int Leg::update(float newPos[3]) {
  if(!(newPos[0] == oldPos[0] && newPos[1] == oldPos[1] && newPos[2] == oldPos[2])) {
  float legLength = sqrt(pow(newPos[0], 2) + pow(newPos[2], 2));
  float HF = sqrt(pow(legLength - this->coxaLength, 2) + pow(newPos[1], 2));
  float a1 = atan2(legLength - this->coxaLength, newPos[1]);
  float a2 = acos(((pow(this->tibiaLength, 2) - pow(this->femurLength, 2)) - pow(HF, 2)) / (-2 * this->femurLength * HF));
  // float a2 = acos(((pow(this->femurLength, 2) - pow(this->tibiaLength, 2)) + pow(HF, 2)) / (2 * this->femurLength * HF));

  float b1 = acos((pow(HF, 2) - pow(this->tibiaLength, 2) - pow(this->femurLength, 2)) / (-2 * this->femurLength * this->tibiaLength));
  // float b1 = ( 90 - (((acos((pow(this->femurLength, 2) + pow(this->tibiaLength, 2) - pow(HF, 2)) / (2 * this->femurLength * this->tibiaLength))) * 180) / LEG_PI));
  if (!inverted){
    this->femurAngle = 270 + (-(a1 + a2) * 180 / LEG_PI);
    // this->tibiaAngle = 90 + (-b1);
    this->tibiaAngle = (-b1 * 180 / LEG_PI) + 180;
    this->coxaAngle = 90 - (atan2(newPos[2], newPos[0]) * 180 / LEG_PI);
  } else {
    this->femurAngle = ((a1 + a2) * 180 / LEG_PI);
    this->tibiaAngle = (b1 * 180 / LEG_PI);
    this->coxaAngle = 90 + (atan2(newPos[2], newPos[0]) * 180 / LEG_PI);
  }

  this->oldPos[0] = newPos[0];
  this->oldPos[1] = newPos[1];
  this->oldPos[2] = newPos[2];
  }
  return 0;
}
*/
