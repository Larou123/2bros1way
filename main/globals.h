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


// --------------------------------- CHARACTER ---------------------------------
// ----------- VARIABLES
int speed = 1;
int characterPos = 20;
int characterX = 5;
int characterY = 73;
const int characterWidht = 32;
const int characterHeigh = 32;
int jumpCounter=0;
bool isJumping=false;
bool wasJumping=false;
int lives = 5;

// ----------- FUNCTIONS
void drawCharacter();

// --------------------------------- GAMEPLAY ---------------------------------
// ----------- VARIABLES
bool inGame = false;

// --------------------------------- MENU ---------------------------------
// ----------- VARIABLES
const char *menu_options[3] = {"Start", "Options", "Credits"};
bool inMenu = true;

// --------------------------------- MAP ---------------------------------
// ----------- VARIABLES
int cloudX = 60;
int cloudY = 27;
int distanceCloud = 60;
int ground = 100;

// ----------- FUNCTIONS
void drawMap();

// --------------------------------- ITEM ---------------------------------
// ----------- VARIABLES
bool itemPicked = false;
int itemX = 60;
int itemY = 100;
int itemW = 5;
int itemH = 5;
int itemC = ARCADA_BLACK;
int itemCounter = 0;
bool isThrowing = false;
bool wasThrown = false;
int throwSpeed = 5;

// ----------- FUNCTIONS
void drawItem();

#endif