#pragma once

#define SERVOLRPIN 6
#define SERVOUDPIN 7
#define JOYSTICK_X A1
#define JOYSTICK_Y A2
#define PUSH_BUTTON 8

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

//Stepper

#define LR_1 5
#define LR_2 4
#define LR_3 3
#define LR_4 2 

#define UD_1 12
#define UD_2 11
#define UD_3 10
#define UD_4 9


enum STATES {
    SETUP = -1,

    
};