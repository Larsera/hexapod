#include "Leg.h"

Leg::Leg(float coxaLength, float femurLength, float tibiaLength, uint8_t inverted) {
this->coxaLength = coxaLength;
this->femurLength = femurLength;
this->tibiaLength = tibiaLength;
this->inverted = inverted;
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
  if(!(newPos[0] == oldPos[0] && newPos[1] == oldPos[1] && newPos[2] == oldPos[2])) {
  this->legLength = sqrt(pow(newPos[0], 2) + pow(newPos[2], 2));
  float HF = sqrt(pow(legLength - this->coxaLength, 2) + pow(newPos[1], 2));
  float a1 = atan2(legLength - this->coxaLength, newPos[1]);
  float a2 = acos(((pow(this->femurLength, 2) - pow(this->tibiaLength, 2)) + pow(HF, 2)) / (2 * this->femurLength * HF));

  float b1 = ( 90 - (((acos((pow(this->femurLength, 2) + pow(this->tibiaLength, 2) - pow(HF, 2)) / (2 * this->femurLength * this->tibiaLength))) * 180) / LEG_PI));
  if (!inverted){
    this->femurAngle = 180 + (-(a1 + a2) * 180 / LEG_PI + 90);
    this->tibiaAngle = 90 + (-b1);
    this->coxaAngle = -90 + atan2(newPos[2], newPos[0]) * 180 / LEG_PI;
  } else {
    this->femurAngle = ((a1 + a2) * 180 / LEG_PI - 90);
    this->tibiaAngle = 90 + b1;
    this->coxaAngle = 90 + atan2(newPos[2], newPos[0]) * 180 / LEG_PI;
  }

  this->oldPos[0] = newPos[0];
  this->oldPos[1] = newPos[1];
  this->oldPos[2] = newPos[2];
  }
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
*/
