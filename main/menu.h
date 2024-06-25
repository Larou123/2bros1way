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
  } else if (menu_opt == 1){
    // Reset game state and restart
    characterPos = 0;  // Reset character position
    rightLimit = 50;
    leftLimit = 20;
    characterX = 20;
    lives = 5;
    bossDamage = false;
    bossActive = false;
    bossHP = 100;
    bossX = 530;
    item->active = false;
    inMenu = false;
    inGame = true;
  } else if (menu_opt == 2){
    // Reset game state and restart
    characterPos = 0;  // Reset character position
    rightLimit = 50;
    leftLimit = 20;
    characterX = 20;
    lives = 5;
    bossDamage = false;
    bossActive = false;
    bossHP = 100;
    bossX = 530;
    item->active = false;
    level1 = true;
    level2 = false;
    inMenu = false;
    inCover = true;
  }
}

#endif