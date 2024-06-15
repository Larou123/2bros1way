#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include <Adafruit_Arcada.h>
#include <Adafruit_NeoPixel.h>

#include "globals.h"
#include "map.h"
#include "character.h"
#include "item.h"
#include "enemy.h"
#include "boss.h"
#include "joystick.h"

// Help function to update display
void updateDisplay(){
  drawMap();
  drawCharacter();
  drawEnemy();
  drawBoss();
  // Bomb explosion
  bomb_explode();
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

  // Test joystick
  if (js_getButton()){
    arcada.getCanvas()->setTextColor(ARCADA_WHITE);
    arcada.getCanvas()->setCursor(30, 10);
    arcada.getCanvas()->println("JOYSTICK PRESSED!");
    arcada.blitFrameBuffer(0, 0, true);
  }

  if (js_getDirection() == JS_RIGHT){
    arcada.getCanvas()->setTextColor(ARCADA_WHITE);
    arcada.getCanvas()->setCursor(30, 20);
    arcada.getCanvas()->println("JOYSTICK RIGHT!");
    arcada.getCanvas()->setCursor(50, 30);
    arcada.getCanvas()->println(analogRead(xPin));
    arcada.blitFrameBuffer(0, 0, true);
  }

   else if (js_getDirection() == JS_LEFT){
    arcada.getCanvas()->setTextColor(ARCADA_WHITE);
    arcada.getCanvas()->setCursor(30, 30);
    arcada.getCanvas()->println("JOYSTICK LEFT!");
    arcada.getCanvas()->setCursor(50, 20);
    arcada.getCanvas()->println(analogRead(xPin));
    arcada.blitFrameBuffer(0, 0, true);
  }

  else if (js_getDirection() == JS_UP){
    arcada.getCanvas()->setTextColor(ARCADA_WHITE);
    arcada.getCanvas()->setCursor(30, 40);
    arcada.getCanvas()->println("JOYSTICK UP!");
    arcada.getCanvas()->setCursor(50, 20);
    arcada.getCanvas()->println(analogRead(yPin));
    arcada.blitFrameBuffer(0, 0, true);
  }

  else if (js_getDirection() == JS_DOWN){
    arcada.getCanvas()->setTextColor(ARCADA_WHITE);
    arcada.getCanvas()->setCursor(30, 50);
    arcada.getCanvas()->println("JOYSTICK DOWN!");
    arcada.getCanvas()->setCursor(50, 20);
    arcada.getCanvas()->println(analogRead(yPin));
    arcada.blitFrameBuffer(0, 0, true);
  }
  
  // Jump logic
  if (buttonState & ARCADA_BUTTONMASK_A) {
    if (!jumpPressed) {
      if (!isJumping) {
        isJumping = true;
        jumpVelocity = jumpPower;
        speed = 2;
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
      speed = 1;
      characterY = ground - 32;  // Reset to ground level
      canDoubleJump = false;  // Reset double jump
    }
  }

  // To Left
  if (buttonState & ARCADA_BUTTONMASK_LEFT) {
    facingRight = false; // Schaut nach links
    isRunning = true; // Läuft
    // Move left
    if (!bossActive && characterX == 20 && characterPos >= 0){
      characterPos -= speed;
    }
    moveCharacter(-speed, 0);
  }

  // To Right
  if (buttonState & ARCADA_BUTTONMASK_RIGHT) {
    facingRight = true; // Schaut nach rechts
    isRunning = true; // Läuft
    // Move right
    if (!bossActive && characterX == 50 && characterPos <= 540){
      characterPos += speed;
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
    itemPicked = false;
    itemX += characterPos;
    if (isJumping){
      bouncePower = 2;
    } else {
      bouncePower = 1;
    }
  }

  // Item movement
  // Initial power throw
  if (isThrowing) {
    if (facingRight) {
      throwVelocityX = throwPower;
    } else {
      throwVelocityX = -throwPower;
    }
    throwVelocityY = -throwPower;

    isThrowing = false;
    wasThrown = true;
    hasBounced = false;
  }

  // Item movement after being thrown
  if (wasThrown) {
    itemX += throwVelocityX;
    itemY += throwVelocityY;

    throwVelocityY += gravity;

    if ((itemY + itemH) >= ground) {
      itemY = ground - itemH;

      if (!hasBounced) {
        throwVelocityY = -bouncePower;
        hasBounced = true;
      } else {
        throwVelocityX = 0;
        throwVelocityY = 0;
        wasThrown = false;
        bomb_expl = true;
      }
    }
  }

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

  // Enemy movement
  moveEnemy();

  // Boss movement
  moveBoss();

  // Update display
  updateDisplay();
}

#endif
