#include <Arduino.h>

/***************************************************
This is an example for our Adafruit 16-channel PWM & Servo driver
Servo test - this will drive 16 servos, one after the other

Pick one up today in the adafruit shop!
------> http://www.adafruit.com/products/815

These displays use I2C to communicate, 2 pins are required to
interface. For Arduino UNOs, thats SCL -> Analog 5, SDA -> Analog 4

Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

Written by Limor Fried/Ladyada for Adafruit Industries.
BSD license, all text above must be included in any redistribution
****************************************************/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <ServoFlow.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);

// Depending on your servo make, the pulse width min and max may vary, you
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!

ServoFlow sf = ServoFlow(pwm);

void setup() {
    Serial.begin(9600);
    Serial.println("Robot online");

    pwm.begin();
    pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
    sf.setAll(90);
    delay(100);
    yield();
}

void loop() {

    while(Serial.available()) {
        int deg = Serial.parseInt();
        Serial.println(deg);
        //servos_flow_set(deg);
        sf.set(2, deg);
    }

    //servo_flow_update();
    sf.update();

    delay(10);
}
