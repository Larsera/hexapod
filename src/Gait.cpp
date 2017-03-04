#include "Gait.h"
#include <MemoryFree.h>

Gait::Gait() {

}

// Y: 25 - 100
void Gait::animate() {
  uint32_t now = millis();
  // lerp: startX + (endX - startX) * amount
  this->r1Pos[0] = this->r1Pos[0] + (animSteps[currentAnimStep*3] - this->r1Pos[0]) * ((float)(now - this->lastTime) / 1000);
  this->r1Pos[1] = this->r1Pos[1] + (animSteps[currentAnimStep*3+1] - this->r1Pos[1]) * ((float)(now - this->lastTime) / 1000);
  this->r1Pos[2] = this->r1Pos[2] + (animSteps[currentAnimStep*3+2] - this->r1Pos[2]) * ((float)(now - this->lastTime) / 1000);

  if(abs(animSteps[currentAnimStep*3+1] - this->r1Pos[1]) < 10) {
    getNextAnimStep();
  }

  this->lastTime = millis();
}

float* Gait::getR1() {
  return r1Pos;
}

float Gait::getNextAnimStep() {
  if(currentAnimStep == (sizeof(animSteps)/sizeof(*animSteps) / 3) - 1) {
    currentAnimStep = 0;
  } else {
    currentAnimStep++;
  }
  return animSteps[currentAnimStep];
}
