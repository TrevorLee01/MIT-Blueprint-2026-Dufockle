#include <Wire.h>
#include <Arduino.h>
#include <NewPing.h>
#include <Servo.h> 
#include "config.hpp"

#include "helper.hpp"
#include "sonar.hpp"


void readJoyStick(int pinX, int pinY, int *outputX, int *outputY);
void limitAngle(int *angle);
void moveServo(int *step, int rate, int PIN_1, int PIN_2, int PIN_3, int PIN_4);
//Objects and stuff

// Adafruit_SSD1306 OLED(OLED_WIDTH, OLED_HEIGHT, OLED_WIRE, OLED_RESET);
NewPing SONAR(SONAR_TRIG, SONAR_ECHO, SONAR_DISTANCE);



int stepLR = 0;
int stepUD = 0;

int rateLR = 0;
int rateUD = 0;

int angleLR = 0;
int angleUD = 0;

float servoDeltaTime = 0.0;
float servoTickStart = 0.0;


int distance = 0;

void setup() {
  // pinMode(SERVOLRPIN, OUTPUT);
  // pinMode(SERVOUDPIN, OUTPUT);

  pinMode(JOYSTICK_X, INPUT);
  pinMode(JOYSTICK_Y, INPUT);
  pinMode(PUSH_BUTTON, INPUT);

  pinMode(BUZZER, OUTPUT);

  pinMode(LR_1, OUTPUT);
  pinMode(LR_2, OUTPUT);
  pinMode(LR_3, OUTPUT);
  pinMode(LR_4, OUTPUT);


  pinMode(UD_1, OUTPUT);
  pinMode(UD_2, OUTPUT);
  pinMode(UD_3, OUTPUT);
  pinMode(UD_4, OUTPUT);

  //Start boring aah communication
  Serial.begin(115200);
  Serial.print("Starting");
  Wire.begin();
  Wire.setClock(400000);

  //Start 
  // initOLED(&OLED);
  initSonar();

  // SERVOLR.attach(SERVOLRPIN);
  // SERVOUD.attach(SERVOUDPIN);

  servoTickStart = toSec(micros());
}

void loop() {
  servoDeltaTime = toSec(micros()) - servoTickStart;
  distance = updateSonar(&SONAR);

  if (distance < 20 && distance > 1) {
    beep();
    delay((1/distance) * 10);
  } else {
    digitalWrite(BUZZER, LOW);
  }

  if (servoDeltaTime > 0.01) {
    servoTickStart = toSec(micros());
    readJoyStick(JOYSTICK_X, JOYSTICK_Y, &rateLR, &rateUD);
  
    angleLR += rateLR;
    angleUD += rateUD;
    limitAngle(&angleLR);
    limitAngle(&angleUD);
  }

  // Serial.print("X: ");
  // Serial.println(angleLR);

  // Serial.print("Y: ");
  // Serial.println(angleUD);

  // Move LR
  moveStepper(&stepLR, rateLR, LR_1, LR_2, LR_3, LR_4);
  //Move UD
  moveStepper(&stepUD, rateUD, UD_1, UD_2, UD_3, UD_4);


  delay(1);

}



void readJoyStick(int pinX, int pinY, int *outputX, int *outputY) {
  int rawOutputX = analogRead(pinX);
  int scaledOutputX = map(rawOutputX, 0, 1024, -5, 5);
  *outputX = scaledOutputX;

  int rawOutputY = analogRead(pinY);
  int scaledOutputY = map(rawOutputY, 0, 1024, -5, 5);
  *outputY = scaledOutputY;
}

void limitAngle(int *angle) {
  if (*angle > 180) {
    *angle = 180;
  } 
  if (*angle < 0) {
    *angle = 0;
  }

}

void moveStepper(int *step, int rate, int PIN_1, int PIN_2, int PIN_3, int PIN_4) {
  if (rate < -1) {
    switch (*step) {
      case 0:
        digitalWrite(PIN_1, HIGH);
        digitalWrite(PIN_2, LOW);
        digitalWrite(PIN_3, LOW);
        digitalWrite(PIN_4, LOW);
      break;
      case 1:
        digitalWrite(PIN_1, LOW);
        digitalWrite(PIN_2, HIGH);
        digitalWrite(PIN_3, LOW);
        digitalWrite(PIN_4, LOW);
      break;
      case 2:
        digitalWrite(PIN_1, LOW);
        digitalWrite(PIN_2, LOW);
        digitalWrite(PIN_3, HIGH);
        digitalWrite(PIN_4, LOW);
      break;
      case 3:
        digitalWrite(PIN_1, LOW);
        digitalWrite(PIN_2, LOW);
        digitalWrite(PIN_3, LOW);
        digitalWrite(PIN_4, HIGH);
      break;
    }
    *step += 1;
  }
  if (rate > 1) {
    switch (*step) {
      case 0:
        digitalWrite(PIN_1, LOW);
        digitalWrite(PIN_2, LOW);
        digitalWrite(PIN_3, LOW);
        digitalWrite(PIN_4, HIGH);
        break;
      case 1:
        digitalWrite(PIN_1, LOW);
        digitalWrite(PIN_2, LOW);
        digitalWrite(PIN_3, HIGH);
        digitalWrite(PIN_4, LOW);
        break;
      case 2:
        digitalWrite(PIN_1, LOW);
        digitalWrite(PIN_2, HIGH);
        digitalWrite(PIN_3, LOW);
        digitalWrite(PIN_4, LOW);
        break;
      case 3:
        digitalWrite(PIN_1, HIGH);
        digitalWrite(PIN_2, LOW);
        digitalWrite(PIN_3, LOW);
        digitalWrite(PIN_4, LOW);
        break;
    }
    *step += 1;
  }

  if (*step >= 4) {
    *step = 0;
  }

}