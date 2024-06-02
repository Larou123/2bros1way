#ifndef GLOBALS_H
#define GLOBALS_H

//Adafruit includes
#include <Adafruit_Arcada.h>
#include <Adafruit_NeoPixel.h>


// Arcada and Neopixel defines
#define NEOPIXEL_PIN    8
#define NEOPIXEL_COUNT  5 

Adafruit_Arcada arcada;
Adafruit_NeoPixel neopixels = Adafruit_NeoPixel(NEOPIXEL_COUNT, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);


// Character variables
int speed = 1;
int characterPos = 0;
int characterX = 5;
int characterY = 73;
const int characterWidht = 20;
const int characterHeigh = 32;
int jumpCounter=0;
bool isJumping=false;
bool wasJumping=false;
int lives = 5;

// Gameplay variables
bool inGame = false;

// Menu variables
const char *menu_options[3] = {"Start", "Options", "Credits"};
bool inMenu = true;

//Map variables
int cloudX = 60;
int cloudY = 27;
int distanceCloud = 60;

// Help Functions
void updateDisplay(){
  arcada.blitFrameBuffer(0, 0, true);
}
#endif