#include <Wire.h>
#include <Arduino.h>
#include <NewPing.h>

#include "config.hpp"
#include "screen.hpp"
#include "helper.hpp"
#include "sonar.hpp"

enum STATES currentState = SETUP;

//Objects and stuff

Adafruit_SSD1306 OLED(OLED_WIDTH, OLED_HEIGHT, OLED_WIRE, OLED_RESET);
NewPing SONAR(SONAR_TRIG, SONAR_ECHO, SONAR_DISTANCE);

void setup() {
  //Start boring aah communication
  Serial.begin(115200);
  Serial.print("Starting");
  Wire.begin();
  Wire.setClock(400000);
  SPI.begin();

  //Start 
  initOLED(&OLED);
  initSonar();
}

void loop() {
  updateSonar(&SONAR);

}


