#pragma once
#include <Adafruit_SSD1306.h>




void initOLED(Adafruit_SSD1306 *pScreen);

//Order of top left, top right, bottom right, bottom left
// A          B
// D          C
// REMINDER TO USE SINGLE QUOTES
void displayButtons(Adafruit_SSD1306 *pScreen, char A, char B, char C, char D);

void updateOLED(Adafruit_SSD1306 *pScreen);

