#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <ServoFlow.h>
#include "Leg.h"

Adafruit_PWMServoDriver pwmRight = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwmLeft = Adafruit_PWMServoDriver(0x41);
ServoFlow sfRight = ServoFlow(pwmRight);
ServoFlow sfLeft = ServoFlow(pwmLeft);
Leg l1 = Leg(15, 55, 92);

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
    while(Serial.available()) {
        float deg = Serial.parseFloat();
        Serial.println(deg);
        //sfRight.setAll(deg);
        //sfLeft.setAll(180 - deg);
        float l1Pos[3] = {100, -80 + deg, 0};
        l1.update(l1Pos);
        sfRight.set(0, l1.getCoxaAngle());
        sfRight.set(1, l1.getFemurAngle());
        sfRight.set(2, l1.getTibiaAngle());
        Serial.print("coxaAngle: "); Serial.print(l1.getCoxaAngle());
        Serial.print(", femurAngle: "); Serial.print(l1.getFemurAngle());
        Serial.print(", tibiaAngle: "); Serial.println(l1.getTibiaAngle());

    }

    sfRight.update();
    sfLeft.update();

    delay(5);
}
