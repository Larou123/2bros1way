#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include <Adafruit_Arcada.h>
#include <Adafruit_NeoPixel.h>

#include "globals.h"
#include "map.h"
#include "character.h"
#include "item.h"

// Help function to update display
void updateDisplay(){
  drawMap();
  drawCharacter();
  arcada.blitFrameBuffer(0, 0, true);
}

// Function to show "You Win" screen
void showWinScreen() {
  arcada.getCanvas()->fillScreen(ARCADA_WHITE);
  arcada.getCanvas()->setTextColor(ARCADA_BLACK);
  arcada.getCanvas()->setCursor(50, 40);
  arcada.getCanvas()->println("You Win!");
  arcada.getCanvas()->setCursor(30, 60);
  arcada.getCanvas()->println("Press A to Restart");
  arcada.blitFrameBuffer(0, 0, true);

  while (true) {
    uint8_t buttonState = arcada.readButtons();
    if (buttonState & ARCADA_BUTTONMASK_A) {
      // Reset game state and restart
      characterPos = 0;  // Reset character position
      inGame = true;
      updateDisplay();
      break;
    }
    yield();
  }
}

// Variables for jump physics
float jumpVelocity = 0;
float gravity = 0.5;  // Gravity acceleration
float jumpPower = -5;  // Initial jump velocity for the first jump
float doubleJumpPower = -4;  // Initial jump velocity for the second jump (less negative for a lower jump)
bool canDoubleJump = false;  // To track if a double jump is allowed
bool jumpPressed = false;  // To track if the jump button is pressed

// Movement during game
void moveInGame(){
  uint8_t buttonState = arcada.readButtons();

  // Jump logic
  if (buttonState & ARCADA_BUTTONMASK_A) {
    if (!jumpPressed) {
      if (!isJumping) {
        isJumping = true;
        jumpVelocity = jumpPower;
        canDoubleJump = true;  // Allow double jump
      } else if (canDoubleJump) {
        jumpVelocity = doubleJumpPower;
        canDoubleJump = false;  // Disable double jump after use
      }
      jumpPressed = true;  // Mark the jump button as pressed
    }
  } else {
    jumpPressed = false;  // Reset the jump button status when released
  }

  if (isJumping) {
    moveCharacter(0, jumpVelocity);
    jumpVelocity += gravity;
    if (characterY >= ground - 32) {  // Check if character has landed on the ground
      isJumping = false;
      characterY = ground - 32;  // Reset to ground level
      canDoubleJump = false;  // Reset double jump
    }
  }

  // To Left
  if (buttonState & ARCADA_BUTTONMASK_LEFT) {
    facingRight = false; // Schaut nach links
    isRunning = true; // Läuft
    // Move left
    if (characterX == 20 && characterPos >= 0){
      characterPos--;
    }
    moveCharacter(-speed, 0);
  }

  // To Right
  if (buttonState & ARCADA_BUTTONMASK_RIGHT) {
    facingRight = true; // Schaut nach rechts
    isRunning = true; // Läuft
    // Move right
    if (characterX == 50 && characterPos <= 540){
      characterPos++;
    }
    moveCharacter(speed, 0);
  }

  // Stop running
  if (!(buttonState & (ARCADA_BUTTONMASK_LEFT | ARCADA_BUTTONMASK_RIGHT))) {
    isRunning = false; // Steht
  }

  // Throw item
  if ((buttonState & ARCADA_BUTTONMASK_B) && itemPicked) {
    isThrowing = true;
    itemX += characterPos;
    itemCounter = 5;
    itemPicked = false;
  }

  // Linear movement
  if (isThrowing){
    itemX += throwSpeed;
  }

  // Diagonal movement
  if (wasThrown && itemY < 100){
    itemX += throwSpeed/2;
    itemY += throwSpeed/2;
  }

  // Start diagonal movement
  if (itemCounter == 0){
      isThrowing = false;
      itemY += throwSpeed/2;
      wasThrown = true;
  }

  // Stop diagonal movement
  if (itemY >= 100){
      wasThrown = false;
  }

  itemCounter--;

  // Check win condition
  if (characterPos >= 540) { // Adjusting the win condition for easier testing
    showWinScreen();
  }
}

void game(){
  // Show lives
  show_lives();

  // Start button presses
  if (arcada.readButtons() & ARCADA_BUTTONMASK_START){
    inGame = false;
    inMenu = true;
  }

  // Movement
  moveInGame();

  // Pick item
  pickItem();

  // Update display
  updateDisplay();
}

#endif
