#include "config.hpp"
#include "helper.hpp"

#include <Adafruit_SSD1306.h>

//Wokwi was the goat for testing this
// I might consider moving this to a class idk

int leftAlign = OLED_WIDTH/5;
int row0 = 0;
int row1 = 8;
int row2 = 16;
int row3 = 24;
int row4 = 32;
int row5 = 40;
int row6 = 48;
int row7 = 56;

// Refresh rate variables
float screenTickStart = 0.0;
float screenDeltaTime = 0.0;

void initOLED(Adafruit_SSD1306 *pScreen) {

    pScreen->begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
    pScreen->display();

    
}

//Order of top left, top right, bottom right, bottom left
// A          B
// D          C
// REMINDER TO USE SINGLE QUOTES
void displayButtons(Adafruit_SSD1306 *pScreen, char A, char B, char C, char D) {
    pScreen->setTextSize(1);

    pScreen->setCursor(0, row0);
    pScreen->print(A);

    pScreen->setCursor(OLED_WIDTH - 8, row0);
    pScreen->print(B);

    pScreen->setCursor(OLED_WIDTH - 8, row7);
    pScreen->print(C);

    pScreen->setCursor(0, row7);
    pScreen->print(D);
}


void updateOLED(Adafruit_SSD1306 *pScreen) {
    screenDeltaTime = toSec(micros()) - screenTickStart;

    if (screenDeltaTime >= OLED_REFRESH) {
        pScreen->clearDisplay();

                displayButtons(pScreen, 'I', 'X', 'Y', 'R'); //Init, XOffset, YOffset, Ready

                pScreen->setCursor(leftAlign, row0);
                pScreen->print("NOT READY");



        pScreen->display();
        screenTickStart = toSec(micros());
    }
}
