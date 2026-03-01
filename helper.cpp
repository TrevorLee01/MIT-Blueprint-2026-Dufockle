#include "helper.hpp"
#include "config.hpp"
#include "Arduino.h"

float toSec(float micros) {
    return (float) micros * 1e-6;
}

void beep() {
    digitalWrite(BUZZER, HIGH);
}