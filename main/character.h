#ifndef CHARACTER_H
#define CHARACTER_H

// Global include
#include "globals.h"
#include "char.h"
#include "map_img.h"
#include "item.h"

// Sprites für die Laufanimation
const unsigned short *runRightSprites[] = {run_frame_0, run_frame_2};
const unsigned short *runLeftSprites[] = {run_frame_1, run_frame_3};
const unsigned char *runRightMasks[] = {run_frame_0_mask, run_frame_2_mask};
const unsigned char *runLeftMasks[] = {run_frame_1_mask, run_frame_3_mask};


// Sprites für die Sprunganimation
const unsigned short *jumpRightSprite = char_jump_right;
const unsigned short *jumpLeftSprite = char_jump_left;
const unsigned char *jumpRightMask = char_jump_right_mask;
const unsigned char *jumpLeftMask = char_jump_left_mask;

int currentSprite = 0; // Aktuelles Sprite

// Zeitsteuerung für die Animation
unsigned long lastFrameChangeChar = 0;

// Richtung des Charakters
bool facingRight = true; // True = rechts, False = links
bool isRunning = false; // True = läuft, False = steht

void drawCharacter() {
  // Überprüfe, ob genug Zeit vergangen ist, um das Sprite zu wechseln
  unsigned long currentMillis = millis();
  if (currentMillis - lastFrameChangeChar >= frameDelay) {
    lastFrameChangeChar = currentMillis;
    if (isRunning && !isJumping) {
      currentSprite = (currentSprite + 1) % 2; // Wechsel zwischen den Lauf-Sprites
    } else {
      currentSprite = 0; // Standbild oder Sprungbild
    }
}

  // Zeichne das aktuelle Sprite basierend auf der Richtung und dem Zustand (springend oder laufend)
  if (isJumping) {
    if (facingRight) {
      arcada.getCanvas()->drawRGBBitmap(characterX, characterY, jumpRightSprite, jumpRightMask, characterWidht, characterHeigh);
    } else {
      arcada.getCanvas()->drawRGBBitmap(characterX, characterY, jumpLeftSprite, jumpLeftMask, characterWidht, characterHeigh);
    }
  } else {
    if (facingRight) {
      arcada.getCanvas()->drawRGBBitmap(characterX, characterY, runRightSprites[currentSprite], runRightMasks[currentSprite], characterWidht, characterHeigh);
    } else {
      arcada.getCanvas()->drawRGBBitmap(characterX, characterY, runLeftSprites[currentSprite], runLeftMasks[currentSprite], characterWidht, characterHeigh);
    }
  }

  // If item picked, then draw it next to the character
  if (item->picked) {
    item->itemX = characterX + (facingRight ? 27 : -5);
    item->itemY = characterY + 5;
    drawItem(item->itemX,item->itemY);  
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

  if (characterX < leftLimit) {
    characterX = leftLimit;
  }

  if (characterX > rightLimit) {
    characterX = rightLimit;
  }
}

// Show current lives in neopixels
void show_lives() {
  neopixels.clear();
  for (uint8_t i = 0; i < lives; i++) {
    if (lives == 3){
      //orange
      neopixels.setPixelColor(i, neopixels.Color(15, 7, 0));
    } else if (lives == 1 || lives == 2){
      //red
      neopixels.setPixelColor(i, neopixels.Color(15, 0, 0));
    } else{
      //green
      neopixels.setPixelColor(i, neopixels.Color(0, 15, 0));
    }
  }
  neopixels.show();
  if (lives == 0) showGameOverScreen();
}

//--------------------------- VOGEL -------------------------------------------------------------
// Sprites für die Flieganimation
const unsigned short *flyRightSprites[] = {companionRightUp, companionRightDown};
const unsigned short *flyLeftSprites[] = {companionLeftUp, companionLeftDown};
const unsigned char *flyRightMasks[] = {companionRightUp_mask, companionRightDown_mask};
const unsigned char *flyLeftMasks[] = {companionLeftUp_mask, companionLeftDown_mask};

int currentSpriteComp = 0; // Aktuelles Sprite

// Zeitsteuerung für die Animation
unsigned long lastFrameChangeComp = 0;

void drawCompanion() {
  // Überprüfe, ob genug Zeit vergangen ist, um das Sprite zu wechseln
  unsigned long currentMillisComp = millis();
  if (currentMillisComp - lastFrameChangeComp >= 300) {
    lastFrameChangeComp = currentMillisComp;
    currentSpriteComp = (currentSpriteComp + 1) % 2; // Wechsel zwischen den Lauf-Sprites
  }
  // Zeichne das aktuelle Sprite basierend auf der Richtung und dem Zustand (springend oder laufend)

  if (flyRight){
    arcada.getCanvas()->drawRGBBitmap(companionX, companionY, flyRightSprites[currentSpriteComp], flyRightMasks[currentSpriteComp], companionWidht, companionHeigh);
  } else{
    arcada.getCanvas()->drawRGBBitmap(companionX, companionY, flyLeftSprites[currentSpriteComp], flyLeftMasks[currentSpriteComp], companionWidht, companionHeigh);
  }
  //arcada.getCanvas()->fillRect(companionX, companionY,companionWidht, companionHeigh,ARCADA_WHITE);
}

void laserCollision(){
  if (item->itemX-characterPos >= 0 && item->itemX-characterPos <= 155 && laser_active && !itemCollision &&  (abs(laserX+3 - (item->itemX-characterPos)) <= 2 || abs(laserX - (item->itemX-characterPos)-item->itemW) <= 2) && abs(laserY - item->itemY) <= 16){
    itemCollision = true;
  }
  
  if (laser_active && !bossDamageLaser && laserY+2 >= bossY+20 && laserX >= bossX - characterPos && laserX <= bossX-characterPos+29){
    bossHP -= 20;
    bossDamageLaser = true;
  }
}

// Move character
void moveCompanion(int nx, int ny) {
  // Update character position
  companionX += nx;
  companionY += ny;

  // Set limits at the borders
  if (companionX < leftLimit) {
    companionX = leftLimit;
  }

  if (companionX > 140-companionWidht) {
    companionX = 140-companionWidht;
  }

  if (companionY < upLimit) {
    companionY = upLimit;
  }

  if (companionY > downLimit) {
    companionY = downLimit;
  }

  //set laser
  if (!laser_active){
    laserX = companionX + (flyRight ? companionWidht+3 : 0);
    laserY = companionY+20;
    bossDamageLaser = false;
  }

  laserCollision();
}
#endif