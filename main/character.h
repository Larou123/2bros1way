#ifndef CHARACTER_H
#define CHARACTER_H

// Global include
#include "globals.h"
#include "char.h"
#include "map_img.h"
#include "item.h"

// Draw character
void drawCharacter() {
  arcada.getCanvas()->drawRGBBitmap(characterX, characterY ,char_man,char_man_mask,32, 32);
  if (itemPicked){
    drawItem(characterX + 27,characterY+15, itemW, itemH, itemC);
  }
}

// Move character
void moveCharacter(int nx, int ny) {
  // Update character position
  characterX += nx;
  characterY += ny;

  // Set limits at the borders
  if (characterX > 156 ){
    characterX = 5;
    characterPos = 0;
    lives--;
  }

  if (characterX < 0 ){
    characterX = 0;
  }
   
  // Draw new position
  drawCharacter();
  updateDisplay();
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