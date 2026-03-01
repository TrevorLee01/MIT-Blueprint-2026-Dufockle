#pragma once

//SPI Pins


// OLED
#define OLED_ADDR 0x3C
#define OLED_WIRE &Wire
#define OLED_HEIGHT 128
#define OLED_WIDTH 64
#define OLED_RESET -1
#define OLED_REFRESH 1/10.0


//Sonar
#define SONAR_ECHO 12
#define SONAR_TRIG 13
#define SONAR_DISTANCE 350
#define SONAR_RATE (20/1000.00)

enum STATES {
    SETUP = -1,

    
};