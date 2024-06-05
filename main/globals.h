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

// --------------------------------- MAP ---------------------------------
// ----------- VARIABLES
int cloudX = 60;
int cloudY = 27;
int distanceCloud = 60;
int ground = 110;

// ----------- FUNCTIONS
void drawMap();

// --------------------------------- CHARACTER ---------------------------------
// ----------- VARIABLES
int speed = 1;
int characterPos = 0;
int characterX = 20;
int characterY = ground - 32;
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



// --------------------------------- ITEM ---------------------------------
// ----------- VARIABLES
bool itemPicked = false;
int itemW = 5;
int itemH = 5;
int itemX = 60;
int itemY = ground-itemH;
int itemC = ARCADA_BLACK;
int itemCounter = 0;
bool isThrowing = false;
bool wasThrown = false;
int throwSpeed = 5;

// ----------- FUNCTIONS
void drawItem();

#endif