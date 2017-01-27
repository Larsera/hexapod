#ifndef ServoFlow_h
#define ServoFlow_h

#include "Arduino.h"
#include <Adafruit_PWMServoDriver.h>

#define SERVO_FLOW_NUM 9
#define SERVO_PWM_MIN  155 // 135 at 50 Hz, 160 at 60 Hz. This is the 'minimum' pulse length count (out of 4096)
#define SERVO_PWM_MAX  550 // 550 at 50 Hz, 615 at 60 Hz. This is the 'maximum' pulse length count (out of 4096)

class ServoFlow {
public:
    ServoFlow(Adafruit_PWMServoDriver s);
    void set(uint8_t servo, uint16_t degree);
    void setAll(uint16_t degree);
    void update();
private:
    Adafruit_PWMServoDriver s;
    uint16_t positions[SERVO_FLOW_NUM * 2] = {};
    uint8_t accTbl[10] = {1, 5, 10, 10, 15, 15, 15, 15, 17, 19};

    void setDegree(uint8_t servo, uint16_t degree);
};

#endif
