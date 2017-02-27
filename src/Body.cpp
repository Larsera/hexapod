#include "Body.h"

#define BODY_PERF_N

Body::Body(Adafruit_PWMServoDriver pwmR, Adafruit_PWMServoDriver pwmL) {
  this->pwmR = pwmR;
  this->pwmL = pwmL;
  this->sfR =  new ServoFlow(pwmR);
  this->sfL =  new ServoFlow(pwmL);
  // Set servos to initial 90 degrees
  // sfR->setAll(90);
  // sfL->setAll(90);

}

int Body::update() {
  // Reading analog and mapping one value takes ~0.170 ms
  int x = analogRead(0);
  int y = analogRead(1);
  int z = analogRead(2);

  float mx = map(x, 0, 1024, -75, 120);
  float my = map(y, 0, 1024, -75, 120);
  float mz = map(z, 0, 1024, -75, 120);

  float r1Pos[3] = {100 + mx, -50 + my,  mz};
  float r2Pos[3] = {100 + mx, -50 + my,  mz};
  float r3Pos[3] = {100 + mx, -50 + my,  mz};
  float l1Pos[3] = {100 + mx, -50 + my,  mz};
  float l2Pos[3] = {100 + mx, -50 + my,  mz};
  float l3Pos[3] = {100 + mx, -50 + my,  mz};

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

  sfR->set(0, leg[0].getCoxaAngle());
  sfR->set(1, leg[0].getFemurAngle());
  sfR->set(2, leg[0].getTibiaAngle());
  sfR->set(3, leg[1].getCoxaAngle());
  sfR->set(4, leg[1].getFemurAngle());
  sfR->set(5, leg[1].getTibiaAngle());
  sfR->set(6, leg[2].getCoxaAngle());
  sfR->set(7, leg[2].getFemurAngle());
  sfR->set(8, leg[2].getTibiaAngle());

  sfL->set(0, leg[3].getCoxaAngle());
  sfL->set(1, leg[3].getFemurAngle());
  sfL->set(2, leg[3].getTibiaAngle());
  sfL->set(3, leg[4].getCoxaAngle());
  sfL->set(4, leg[4].getFemurAngle());
  sfL->set(5, leg[4].getTibiaAngle());
  sfL->set(6, leg[5].getCoxaAngle());
  sfL->set(7, leg[5].getFemurAngle());
  sfL->set(8, leg[5].getTibiaAngle());

  // Serial.print("coxaAngleR: "); Serial.print(leg[0].getCoxaAngle());
  // Serial.print(", femurAngle: "); Serial.print(leg[0].getFemurAngle());
  // Serial.print(", tibiaAngle: "); Serial.println(leg[0].getTibiaAngle());

  // Serial.print("coxaAngleR: "); Serial.print(leg[0].getFemurAngle());
  // Serial.print(",  "); Serial.print(         leg[1].getFemurAngle());
  // Serial.print(",  "); Serial.println(       leg[2].getFemurAngle());

  // Serial.print("coxaAngleL: "); Serial.print(leg[3].getCoxaAngle());
  // Serial.print(", femurAngleL: "); Serial.print(leg[3].getFemurAngle());
  // Serial.print(", tibiaAngleL: "); Serial.println(leg[3].getTibiaAngle());

  #ifdef BODY_PERF
  unsigned long SFStart = micros();
  #endif
  sfR->update();
  sfL->update();
  #ifdef BODY_PERF
  unsigned long SFEnd = micros();
  unsigned long SFDelta = SFEnd - SFStart;
  Serial.print(F("\t SF->update(): "));
  Serial.println(SFDelta);
  #endif

  return 0;
}
