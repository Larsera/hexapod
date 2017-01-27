#include "Leg.h"

Leg::Leg(uint16_t limits[6], uint16_t lengths[3], uint8_t inverted) {
  this->legLength = sqrt(pow(femur, 2) + pow(tibia, 2));
}

Leg::update() {
  float legLength = sqrt(pow(femur, 2) + pow(tibia, 2));
  float gamma = atan2(newPos[0], newPos[1]);
}
