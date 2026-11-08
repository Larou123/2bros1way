#ifndef CHARACTER_H
#define CHARACTER_H

// Global include
#include "globals.h"
#include "char.h"
#include "map_img.h"
#include "item.h"
// ------------------ Character movement animation
// Sprites for walking
const unsigned short *runRightSprites[] = {run_frame_0, run_frame_2,charsword1, charsword1_run};
const unsigned short *runLeftSprites[] = {run_frame_1, run_frame_3,charsword1_left, charsword1_run_left};
const unsigned char *runRightMasks[] = {run_frame_0_mask, run_frame_2_mask,charsword1_mask, charsword1_run_mask};
const unsigned char *runLeftMasks[] = {run_frame_1_mask, run_frame_3_mask,charsword1_left_mask, charsword1_run_left_mask};

int currentAnim = 0;

// Sprites for Jump and Double Jump
const unsigned short *jumpRightSprite[] = {char_jump_right,charsword1_jump};
const unsigned short *jumpLeftSprite[] = {char_jump_left,charsword1_jump_left};
const unsigned char *jumpRightMask[] = {char_jump_right_mask,charsword1_jump_mask};
const unsigned char *jumpLeftMask[] = {char_jump_left_mask,charsword1_jump_left_mask};
int currentJump = 0;

int currentSprite = 0; // Aktuelles Sprite

// Timing
unsigned long lastFrameChangeChar = 0;

// Direction
bool facingRight = true; // True = right, False = left
bool isRunning = false; // True = walking, False = standing

// Draw the character depending on wich state he is
void drawCharacter() {
  // Check if enough time has passed to change the sprite
  unsigned long currentMillis = millis();
  if (currentMillis - lastFrameChangeChar >= frameDelay) {
    lastFrameChangeChar = currentMillis;
    if (isRunning && !isJumping) {
      currentSprite = (currentSprite + 1) % 2; // Wechsel zwischen den Lauf-Sprites
    } else {
      currentSprite = 0; // Standbild oder Sprungbild
    }
}

  //Draw the current sprite based on direction and state (jumping or running)
  if (isJumping) {
    if (facingRight) {
      arcada.getCanvas()->drawRGBBitmap(characterX, characterY, jumpRightSprite[currentJump], jumpRightMask[currentJump], characterWidht, characterHeigh);
    } else {
      arcada.getCanvas()->drawRGBBitmap(characterX, characterY, jumpLeftSprite[currentJump], jumpLeftMask[currentJump], characterWidht, characterHeigh);
    }
  } else {
    if (facingRight) {
      arcada.getCanvas()->drawRGBBitmap(characterX, characterY, runRightSprites[currentSprite + currentAnim], runRightMasks[currentSprite + currentAnim], characterWidht, characterHeigh);
    } else {
      arcada.getCanvas()->drawRGBBitmap(characterX, characterY, runLeftSprites[currentSprite + currentAnim], runLeftMasks[currentSprite + currentAnim], characterWidht, characterHeigh);
    }
  }

  // If item picked, then draw it next to the character
  if (item->picked && level1) {
    item->itemX = characterX + (facingRight ? 27 : -5);
    item->itemY = characterY + 5;
    drawItem(item->itemX,item->itemY);  
  } else if(item->picked && level2){
    currentAnim = 2;
    currentJump = 1;
  } else if(!item->picked && level2 ){
    currentAnim = 0;
    currentJump = 0;
  }
}

// ------------------ Character attack animation
// Sprites
const unsigned short *attackRightSprites[] = {charsword1,charsword2,charsword3};
const unsigned short *attackLeftSprites[] = {charsword1_left,charsword2_left,charsword3_left};
const unsigned char *attackRightMasks[] = {charsword1_mask,charsword2_mask,charsword3_mask};
const unsigned char *attackLeftMasks[] = {charsword1_left_mask,charsword2_left_mask,charsword3_left_mask};
int currentSpriteA = 0; // Aktuelles Sprite

// Timing
unsigned long lastFrameChangeA = 0;

// Draws the attack animation using the sprites
void drawAttackAnim(){
  unsigned long currentMillisA = millis();
  if (currentMillisA - lastFrameChangeA >= 175) {
    lastFrameChangeA = currentMillisA;
    currentSpriteA = (currentSpriteA + 1) % 4;
  }
  if (currentSpriteA < 2){
    if (facingRight){
      arcada.getCanvas()->drawRGBBitmap(characterX, characterY, attackRightSprites[currentSpriteA], attackRightMasks[currentSpriteA], characterWidht, characterHeigh);
    } else {
      arcada.getCanvas()->drawRGBBitmap(characterX, characterY, attackLeftSprites[currentSpriteA], attackLeftMasks[currentSpriteA], characterWidht, characterHeigh);
    } 
  } else if (currentSpriteA == 2){
    attackDamage = true;
    if (facingRight){
      arcada.getCanvas()->drawRGBBitmap(characterX, characterY-13, attackRightSprites[currentSpriteA], attackRightMasks[currentSpriteA], 45, 45);
    } else {
      arcada.getCanvas()->drawRGBBitmap(characterX, characterY-13, attackLeftSprites[currentSpriteA], attackLeftMasks[currentSpriteA], 45, 45);
    } 
  } else {
    if (facingRight){
      arcada.getCanvas()->drawRGBBitmap(characterX, characterY, charsword1, charsword1_mask, characterWidht, characterHeigh);
    } else {
      arcada.getCanvas()->drawRGBBitmap(characterX, characterY, charsword1_left, charsword1_left_mask, characterWidht, characterHeigh);
    }
    attackActive = false;
    bossDamage = false;
    attackDamage = false;
    if (bossHP <= 0){
      showWinScreen();
    }
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

//--------------------------- COMPANION -------------------------------------------------------------
// ------------------ Companion movement animation
// Sprites
const unsigned short *flyRightSprites[] = {companionRightUp, companionRightDown};
const unsigned short *flyLeftSprites[] = {companionLeftUp, companionLeftDown};
const unsigned char *flyRightMasks[] = {companionRightUp_mask, companionRightDown_mask};
const unsigned char *flyLeftMasks[] = {companionLeftUp_mask, companionLeftDown_mask};

int currentSpriteComp = 0; // Aktuelles Sprite

// Timing
unsigned long lastFrameChangeComp = 0;

void drawCompanion() {
  // Check if enough time has passed to change the sprite
  unsigned long currentMillisComp = millis();
  if (currentMillisComp - lastFrameChangeComp >= 300) {
    lastFrameChangeComp = currentMillisComp;
    currentSpriteComp = (currentSpriteComp + 1) % 2; // Wechsel zwischen den Lauf-Sprites
  }
  // Draw the current sprite based on direction

  if (flyRight){
    arcada.getCanvas()->drawRGBBitmap(companionX, companionY, flyRightSprites[currentSpriteComp], flyRightMasks[currentSpriteComp], companionWidht, companionHeigh);
  } else{
    arcada.getCanvas()->drawRGBBitmap(companionX, companionY, flyLeftSprites[currentSpriteComp], flyLeftMasks[currentSpriteComp], companionWidht, companionHeigh);
  }
  //arcada.getCanvas()->fillRect(companionX, companionY,companionWidht, companionHeigh,ARCADA_WHITE);
}

// Controlls the possible laser collisions
void laserCollision(){
  // Comproves if laser has impacted item while item is flying
  if (item->itemX-characterPos >= 0 && item->itemX-characterPos <= 155 && laser_active && !itemCollision &&  (abs(laserX+3 - (item->itemX-characterPos)) <= 3 || abs(laserX - (item->itemX-characterPos)-item->itemW) <= 3) && laserY+3 >= item->itemY && laserY <= item->itemY+25){
    itemCollision = true;
  }
  
  // Comproves if laser has impacted Boss
  if (laser_active && !bossDamageLaser && laserY+2 >= bossY+20 && laserX >= bossX-characterPos && laserX+3 <= bossX+37-characterPos){
    bossHP -= 20;
    //if boss killed, game win screen
    if (bossHP <= 0){
      if (level1){
        arcada.getCanvas()->fillRoundRect(10,ground+8,(bossHP/100)*140,8,8,ARCADA_ORANGE);
        startLevel2Screen();
      } else if (level2){
        arcada.getCanvas()->fillRoundRect(10,ground+8,(bossHP/100)*140,8,8,ARCADA_RED);
        showWinScreen();
      }
      
    }
    bossDamageLaser = true;
  }
}

// Move companion
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

  // Set laser
  if (!laser_active){
    laserX = companionX + (flyRight ? companionWidht+3 : -3);
    laserY = companionY+20;
    bossDamageLaser = false;
  }

  laserCollision();
}

// Show in wich direction the laser points
void drawLaserDirection(){
  if (!laser_active){
    if (laser_pre_direction == JS_RIGHT){
      arcada.getCanvas()->fillTriangle(laserDirectionX,laserDirectionY-4,laserDirectionX,laserDirectionY,laserDirectionX+3,laserDirectionY-1.5,ARCADA_CYAN);
    } else if (laser_pre_direction == JS_LEFT){
      arcada.getCanvas()->fillTriangle(laserDirectionX,laserDirectionY-4,laserDirectionX,laserDirectionY,laserDirectionX-3,laserDirectionY-1.5,ARCADA_CYAN);
    } else if (laser_pre_direction == JS_UP){
      arcada.getCanvas()->fillTriangle(laserDirectionX-2,laserDirectionY,laserDirectionX+2,laserDirectionY,laserDirectionX,laserDirectionY-2,ARCADA_CYAN);
    } else{
     arcada.getCanvas()->fillTriangle(laserDirectionX-2,laserDirectionY+3,laserDirectionX+2,laserDirectionY+3,laserDirectionX,laserDirectionY+5,ARCADA_CYAN);
    }
  }
}
#endif