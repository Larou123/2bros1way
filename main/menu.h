#ifndef MENU_H
#define MENU_H

// Global include
#include "globals.h"
#include <Adafruit_GFX.h>

//Menu selection
void menu(){
  arcada.getCanvas()->fillScreen(ARCADA_WHITE);
  
  uint8_t menu_opt = arcada.menu(menu_options, 3, ARCADA_WHITE, ARCADA_BLACK);

  if (menu_opt == 0){
    inMenu = false;
    inGame = true;
    updateDisplay();
  }
}

#endif