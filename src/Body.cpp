#include "Body.h"

#define BODY_PERF_N

Body::Body(Adafruit_PWMServoDriver pwmR, Adafruit_PWMServoDriver pwmL) {
  this->pwmR = pwmR;
  this->pwmL = pwmL;
  this->sfRight =  new ServoFlow(pwmR);
  this->sfLeft =  new ServoFlow(pwmL);
  // Set servos to initial 90 degrees
  // sfRight->setAll(90);
  // sfLeft->setAll(90);

}

int Body::update() {
  // reading analog and map takes ~0.170 ms
  int a = analogRead(0);
  float deg = map(a, 0, 1024, -75, 120);
  // -39, 120
  float r1Pos[3] = {100 , -50 , -50 + deg};
  float r2Pos[3] = {100 , -50 , 0   - deg};
  float r3Pos[3] = {100 , -50 , 50  + deg};
  float l1Pos[3] = {100 , -50 , -50 - deg};
  float l2Pos[3] = {100 , -50 , 0   + deg};
  float l3Pos[3] = {100 , -50 , 50  - deg};

  #ifdef BODY_PERF
  unsigned long start = micros();
  #endif
  leg[0].update(r1Pos);
  leg[1].update(r2Pos);
  leg[2].update(r3Pos);
  leg[3].update(l1Pos);
  leg[4].update(l2Pos);
  leg[5].update(l3Pos);
  #ifdef BODY_PERF
  unsigned long end = micros();
  unsigned long delta = end - start;
  Serial.print("leg.update(): ");
  Serial.print(delta);
  #endif

  sfRight->set(0, leg[0].getCoxaAngle());
  sfRight->set(1, leg[0].getFemurAngle());
  sfRight->set(2, leg[0].getTibiaAngle());
  sfRight->set(3, leg[1].getCoxaAngle());
  sfRight->set(4, leg[1].getFemurAngle());
  sfRight->set(5, leg[1].getTibiaAngle());
  sfRight->set(6, leg[2].getCoxaAngle());
  sfRight->set(7, leg[2].getFemurAngle());
  sfRight->set(8, leg[2].getTibiaAngle());

  sfLeft->set(0, leg[3].getCoxaAngle());
  sfLeft->set(1, leg[3].getFemurAngle());
  sfLeft->set(2, leg[3].getTibiaAngle());
  sfLeft->set(3, leg[4].getCoxaAngle());
  sfLeft->set(4, leg[4].getFemurAngle());
  sfLeft->set(5, leg[4].getTibiaAngle());
  sfLeft->set(6, leg[5].getCoxaAngle());
  sfLeft->set(7, leg[5].getFemurAngle());
  sfLeft->set(8, leg[5].getTibiaAngle());

  // Serial.print("coxaAngleR: "); Serial.print(leg[0].getCoxaAngle());
  // Serial.print("\tcoxaAngleL: "); Serial.println(leg[3].getCoxaAngle());
  //Serial.print(", femurAngle: "); Serial.print(l1.getFemurAngle());
  // Serial.print(", femurAngle: "); Serial.println(r1.getFemurAngle());
  //Serial.print(", tibiaAngle: "); Serial.print(l1.getTibiaAngle());
  //Serial.print(", tibiaAngle: "); Serial.println(r1.getTibiaAngle());

  #ifdef BODY_PERF
  unsigned long SFStart = micros();
  #endif
  sfRight->update();
  sfLeft->update();
  #ifdef BODY_PERF
  unsigned long SFEnd = micros();
  unsigned long SFDelta = SFEnd - SFStart;
  Serial.print("\t SF->update(): ");
  Serial.println(SFDelta);
  #endif

  return 0;
}
