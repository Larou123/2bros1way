#ifndef CHARACTER_H
#define CHARACTER_H

// Global include
#include "globals.h"

// Draw character
void drawCharacter() {
  arcada.display->fillRect(characterX, characterY, characterWidht, characterHeigh, ARCADA_BLACK);
}

// Move character
void moveCharacter(int nx, int ny) {
  // Clear previous character position
  arcada.display->fillRect(characterX, characterY, characterWidht, characterHeigh, ARCADA_CYAN);

  // Update character position
  characterX += nx;
   characterY += ny;

  // Set limits at the borders
  if (characterX < 0 || characterX > 156 ){
    characterX = 84;
    lives--;
  }
   
  // Draw new position
  drawCharacter();
}

// Show current lives in neopixels
void show_lives(){
  neopixels.clear();
  for (uint8_t i = 0; i < lives;i++){
    neopixels.setPixelColor(i,neopixels.Color(0,15,0));
  }
  neopixels.show();
  if (lives == 0) lives = 5;
}

#endif