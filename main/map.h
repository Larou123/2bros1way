#ifndef MAP_H
#define MAP_H

// Global include
#include "globals.h"

// Draws map
void drawMap() {
  // land
  arcada.display->fillRect(0, 94, 170, 74, ARCADA_GREEN);

  // sky
  arcada.display->fillRect(0, 0, 170, 94, ARCADA_CYAN);

  // obstacles
  //cada.display->fillRect(40, 15, 10, 10, ARCADA_RED); 
  //arcada.display->fillRect(70, 50, 10, 10, ARCADA_RED); 

  // border
  //arcada.display->drawRect(10, 10, 100, 60, ARCADA_WHITE);
}

#endif