#include <Arduino.h>
#include <MemoryFree.h>
#include "Body.h"

Adafruit_PWMServoDriver pwmRight = Adafruit_PWMServoDriver(0x40); // = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwmLeft = Adafruit_PWMServoDriver(0x41); // = Adafruit_PWMServoDriver(0x41);
Body *b = new Body(pwmRight, pwmLeft);

void setup() {
  // PWM setup
    pwmRight.begin();
    pwmLeft.begin();
    pwmRight.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
    pwmLeft.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

    Serial.begin(9600);
    Serial.print("Robot active, free SRAM: ");
    Serial.println(freeMemory());

    delay(20);
    yield();
}

void loop() {
  unsigned long start = micros();
  b->update();
  unsigned long end = micros();
  unsigned long delta = end - start;
  Serial.print(", update: ");
  Serial.println(delta);

  delay(20);
}
