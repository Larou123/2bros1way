#ifndef GLOBALS_H
#define GLOBALS_H

#include <Adafruit_Arcada.h>
#include <Adafruit_NeoPixel.h>
#include "item_img.h" // Hinzufügen der Item-Definitionen
#include "item.h"

// Arcada and Neopixel defines
#define NEOPIXEL_PIN    8
#define NEOPIXEL_COUNT  5 

extern Adafruit_Arcada arcada;
extern Adafruit_NeoPixel neopixels;

// --------------------------------- MAP ---------------------------------
// ----------- VARIABLES
extern int cloudX;
extern int cloudY;
extern int distanceCloud;
extern int ground;

// ----------- FUNCTIONS
void drawMap();

// --------------------------------- CHARACTER ---------------------------------
// ----------- VARIABLES
extern int speed;
extern int characterPos;
extern int characterX;
extern int characterY;
extern const int characterWidht;
extern const int characterHeigh;
extern int jumpCounter;
extern bool isJumping;
extern bool wasJumping;
extern int lives;

// Sprite-Daten für die Laufanimation
extern const unsigned short run_frame_0[1024];
extern const unsigned short run_frame_1[1024];
extern const unsigned short run_frame_2[1024];
extern const unsigned short run_frame_3[1024];

// ----------- FUNCTIONS
void drawCharacter();

// --------------------------------- GAMEPLAY ---------------------------------
// ----------- VARIABLES
extern bool inGame;

// --------------------------------- MENU ---------------------------------
// ----------- VARIABLES
extern const char *menu_options[3];
extern bool inMenu;

// --------------------------------- ITEM ---------------------------------
// ----------- VARIABLES
extern bool itemPicked;
extern int itemW;
extern int itemH;
extern int itemX;
extern int itemY;
extern int itemC;
extern int itemCounter;
extern bool isThrowing;
extern bool wasThrown;
extern int throwSpeed;
extern Item* currentItem; // Deklaration von currentItem

// ----------- FUNCTIONS
void drawItem(int x, int y, int w, int h, int color);
void pickItem();

#endif