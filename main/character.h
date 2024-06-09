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
unsigned long lastFrameChange = 0;
const unsigned long frameDelay = 100; // Zeit zwischen den Frames in Millisekunden

// Richtung des Charakters
bool facingRight = true; // True = rechts, False = links
bool isRunning = false; // True = läuft, False = steht

void drawCharacter() {
  // Überprüfe, ob genug Zeit vergangen ist, um das Sprite zu wechseln
  unsigned long currentMillis = millis();
  if (currentMillis - lastFrameChange >= frameDelay) {
    lastFrameChange = currentMillis;
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
  if (itemPicked) {
    itemX = characterX + (facingRight ? 27 : -5);
    itemY = characterY + 15;
    drawItem(itemX, itemY, itemW, itemH, itemC);  
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
    neopixels.setPixelColor(i, neopixels.Color(0, 15, 0));
  }
  neopixels.show();
  if (lives == 0) lives = 5;
}

#endif