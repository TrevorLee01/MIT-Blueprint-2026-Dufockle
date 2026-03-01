#include "servo.hpp"
#include "config.hpp"
#include "Arduino.h"

void servoMove(int servoPin, int duty) {
    analogWrite(servoPin, duty);
}