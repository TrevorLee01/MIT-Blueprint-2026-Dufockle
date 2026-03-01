#include <NewPing.h>

#include "config.hpp"
#include "helper.hpp"

float sonarDeltaTime = 0.0;
float sonarTickStart = 0.0;

static int sonarReading = 0;

void initSonar() {
    sonarTickStart = toSec(micros());
}

int updateSonar(NewPing *pSonar) {
    sonarDeltaTime = toSec(micros()) - sonarTickStart;

    if (sonarDeltaTime > SONAR_RATE) {
        sonarReading = pSonar->ping_cm();

    }
    Serial.println(sonarReading);
    return sonarReading;
}