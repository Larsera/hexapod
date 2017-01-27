#include "ServoFlow.h"

ServoFlow::ServoFlow(Adafruit_PWMServoDriver s) {
    this->s = s;
}

void ServoFlow::set(uint8_t servo, uint16_t degree) {
    this->positions[servo*2+1] = degree;
}

void ServoFlow::setAll(uint16_t degree) {
    for(uint8_t s = 0; s < SERVO_FLOW_NUM; s++) {
        set(s, degree);
    }
}

void ServoFlow::update() {
    for(uint8_t servo = 0; servo < SERVO_FLOW_NUM; servo++) {
        if (this->positions[servo*2] == this->positions[(servo*2)+1]) {

        } else {
            int new_deg = this->positions[(servo*2)];

            int diff = map(abs((int)this->positions[(servo*2)+1] - (int)this->positions[(servo*2)]), 0, 180, 0, 10);
            Serial.println(diff);

            if (this->positions[(servo*2)+1] > this->positions[(servo*2)]) {
                new_deg += this->accTbl[diff];
            } else {
                new_deg -= this->accTbl[diff];
            }

            setDegree(servo, new_deg);
            this->positions[(servo*2)] = new_deg;

            //Serial.print("Servo: "); Serial.print(servo);
            //Serial.print(" pos: "); Serial.print(this->positions[(servo*2)]);
            //Serial.print(" target: ");Serial.println(this->positions[(servo*2)+1]);


        }
    }
}

void ServoFlow::setDegree(uint8_t servo, uint16_t degree) {
    uint16_t posPWM = map(degree, 0, 180, SERVO_PWM_MIN, SERVO_PWM_MAX);
    this->s.setPWM(servo, 0, posPWM);
}
