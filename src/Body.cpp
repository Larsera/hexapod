#include "Body.h"

#define BODY_PERF_N

Body::Body(Adafruit_PWMServoDriver pwmR, Adafruit_PWMServoDriver pwmL) {
  this->pwmR = pwmR;
  this->pwmL = pwmL;
  // this->sfRight =  new ServoFlow(pwmR);
  this->sfLeft =  new ServoFlow(pwmL);
  // Set servos to initial 90 degrees
  // sfRight->setAll(90);
  sfLeft->setAll(90);

}

int Body::update() {
  // reading analog and map takes ~0.170 ms
  int a = analogRead(0);
  float deg = map(a, 0, 1024, -75, 120);
  // -39, 120
  float l1Pos[3] = {100 + deg , -50, 0};
  // float r1Pos[3] = {-100, -50 + deg, 0};

  #ifdef BODY_PERF
  unsigned long start = micros();
  #endif
  leg[0].update(l1Pos);
  //leg[3].update(r1Pos);
  #ifdef BODY_PERF
  unsigned long end = micros();
  unsigned long delta = end - start;
  Serial.print("leg.update(): ");
  Serial.print(delta);
  #endif

  sfLeft->set(0, leg[0].getCoxaAngle());
  sfLeft->set(1, leg[0].getFemurAngle());
  sfLeft->set(2, leg[0].getTibiaAngle());
  sfLeft->set(3, leg[0].getCoxaAngle());
  sfLeft->set(4, leg[0].getFemurAngle());
  sfLeft->set(5, leg[0].getTibiaAngle());
  sfLeft->set(6, leg[0].getCoxaAngle());
  sfLeft->set(7, leg[0].getFemurAngle());
  sfLeft->set(8, leg[0].getTibiaAngle());

  // sfRight->set(0, leg[3].getCoxaAngle());
  // sfRight->set(1, leg[3].getFemurAngle());
  // sfRight->set(2, leg[3].getTibiaAngle());
  // sfRight->set(3, leg[3].getCoxaAngle());
  // sfRight->set(4, leg[3].getFemurAngle());
  // sfRight->set(5, leg[3].getTibiaAngle());
  // sfRight->set(6, leg[3].getCoxaAngle());
  // sfRight->set(7, leg[3].getFemurAngle());
  // sfRight->set(8, leg[3].getTibiaAngle());

  //Serial.print("coxaAngle: "); Serial.print(l1.getCoxaAngle());
  //Serial.print(" coxaAngle: "); Serial.println(r1.getCoxaAngle());
  //Serial.print(", femurAngle: "); Serial.print(l1.getFemurAngle());
  //Serial.print(", femurAngle: "); Serial.println(r1.getFemurAngle());
  //Serial.print(", tibiaAngle: "); Serial.print(l1.getTibiaAngle());
  //Serial.print(", tibiaAngle: "); Serial.println(r1.getTibiaAngle());

  #ifdef BODY_PERF
  unsigned long SFStart = micros();
  #endif
  // sfRight->update();
  sfLeft->update();
  #ifdef BODY_PERF
  unsigned long SFEnd = micros();
  unsigned long SFDelta = SFEnd - SFStart;
  Serial.print(", SF->update(): ");
  Serial.print(SFDelta);
  #endif

  return 0;
}
