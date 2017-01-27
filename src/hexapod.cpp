#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <ServoFlow.h>

Adafruit_PWMServoDriver pwmRight = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwmLeft = Adafruit_PWMServoDriver(0x41);
ServoFlow sfRight = ServoFlow(pwmRight);
ServoFlow sfLeft = ServoFlow(pwmLeft);

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
        int deg = Serial.parseInt();
        Serial.println(deg);
        sfRight.setAll(deg);
        sfLeft.setAll(180 - deg);
    }

    sfRight.update();
    sfLeft.update();

    delay(5);
}
