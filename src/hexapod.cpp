#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <ServoFlow.h>
#include "Body.h"

Adafruit_PWMServoDriver pwmRight = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwmLeft = Adafruit_PWMServoDriver(0x41);
ServoFlow sfRight = ServoFlow(pwmRight);
ServoFlow sfLeft = ServoFlow(pwmLeft);
Leg l1 = Leg(13, 55.5, 89, 0);
Leg r1 = Leg(13, 55.5, 89, 1);
Body b = Body();

void setup() {
    Serial.begin(9600);
    Serial.println("Robot online");

    pwmRight.begin();
    pwmRight.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
    pwmLeft.begin();
    pwmLeft.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

    sfRight.setAll(90);
    sfLeft.setAll(90);

    delay(20);
    yield();
}

void loop() {
  int a = analogRead(0);
    //while(Serial.available()) {
        float deg = map(a, 0, 1024, -75, 120); // Serial.parseFloat();
        //Serial.println(deg);
        //sfRight.setAll(deg);
        //sfLeft.setAll(180 - deg);
        // -39, 120
        float l1Pos[3] = {100 + deg, -50 + deg, 0};
        float r1Pos[3] = {-100 - deg, -50 + deg, 0};
        unsigned long start = micros();
        l1.update(l1Pos);
        r1.update(r1Pos);
        unsigned long end = micros();
        unsigned long delta = end - start;
        //Serial.println(delta);

        sfRight.set(0, l1.getCoxaAngle());
        sfRight.set(1, l1.getFemurAngle());
        sfRight.set(2, l1.getTibiaAngle());
        sfRight.set(3, l1.getCoxaAngle());
        sfRight.set(4, l1.getFemurAngle());
        sfRight.set(5, l1.getTibiaAngle());
        sfRight.set(6, l1.getCoxaAngle());
        sfRight.set(7, l1.getFemurAngle());
        sfRight.set(8, l1.getTibiaAngle());

        sfLeft.set(0, r1.getCoxaAngle());
        sfLeft.set(1, r1.getFemurAngle());
        sfLeft.set(2, r1.getTibiaAngle());
        sfLeft.set(3, r1.getCoxaAngle());
        sfLeft.set(4, r1.getFemurAngle());
        sfLeft.set(5, r1.getTibiaAngle());
        sfLeft.set(6, r1.getCoxaAngle());
        sfLeft.set(7, r1.getFemurAngle());
        sfLeft.set(8, r1.getTibiaAngle());
        //Serial.print("coxaAngle: "); Serial.print(l1.getCoxaAngle());
        //Serial.print(" coxaAngle: "); Serial.println(r1.getCoxaAngle());
        //Serial.print(", femurAngle: "); Serial.print(l1.getFemurAngle());
        //Serial.print(", femurAngle: "); Serial.println(r1.getFemurAngle());
        //Serial.print(", tibiaAngle: "); Serial.print(l1.getTibiaAngle());
        //Serial.print(", tibiaAngle: "); Serial.println(r1.getTibiaAngle());

    //}

    sfRight.update();
    sfLeft.update();

    //delay(20);
}
