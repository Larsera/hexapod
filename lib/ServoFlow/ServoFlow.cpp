#include "Arduino.h"
#include "ServoFlow.h"

ServoFlow::ServoFlow(Adafruit_PWMServoDriver s) {
    _s = s;
}

void ServoFlow::set(uint8_t servo, uint16_t degree) {
    _positions[servo*2+1] = degree;
}

void ServoFlow::setAll(uint16_t degree) {
    for(uint8_t s = 0; s < SERVO_FLOW_NUM; s++) {
        set(s, degree);
    }
}

void ServoFlow::update() {
    for(uint8_t servo = 0; servo < SERVO_FLOW_NUM; servo++) {
        if (_positions[servo*2] == _positions[(servo*2)+1]) {

        } else {
            int new_deg = _positions[(servo*2)];

            int diff = map(abs((int)_positions[(servo*2)+1] - (int)_positions[(servo*2)]), 0, 180, 0, 10);
            Serial.println(diff);

            if (_positions[(servo*2)+1] > _positions[(servo*2)]) {
                new_deg += _accTbl[diff];
            } else {
                new_deg -= _accTbl[diff];
            }

            setDegree(servo, new_deg);
            _positions[(servo*2)] = new_deg;

            //Serial.print("Servo: "); Serial.print(servo);
            //Serial.print(" pos: "); Serial.print(_positions[(servo*2)]);
            //Serial.print(" target: ");Serial.println(_positions[(servo*2)+1]);


        }
    }
}

void ServoFlow::setDegree(uint8_t servo, uint16_t degree) {
    uint16_t pos_pwm = map(degree, 0, 180, SERVO_PWM_MIN, SERVO_PWM_MAX);
    _s.setPWM(servo, 0, pos_pwm);
}
