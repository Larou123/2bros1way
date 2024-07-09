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
#include "cover.h"

// Reset stats
void reset_stats(){
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
  item->picked = false;
  currentAnim = 0;
  currentJump = 0;
  laser_active = false;
  fireCanonRight = true;
  fireCanonX = 160;
}

// Help function to update display
void updateDisplay(){
  drawMap();
  if (item->picked && level2 && (arcada.readButtons() & ARCADA_BUTTONMASK_B | attackActive)){
    attackActive = true;
    drawAttackAnim();
  } else {
    drawCharacter();
  }
  drawEnemy();
  drawBoss();
  drawCompanion();
  // Bomb explosion
  bomb_explode();
  showBossHP();
  // Laser
  arcada.getCanvas()->fillCircle(laserX,laserY,3,ARCADA_BLUE);
  drawLaserDirection();
  arcada.blitFrameBuffer(0, 0, true);
}


// Show cover
int startCounter = 100; // Variable to make "Start" appear and disappear at the Cover screen
void showCover() {
  level1 = true;
  level2 = false;
  while (true) {
    if (arcada.readButtons() & ARCADA_BUTTONMASK_START) {
        inCover = false;
        inGame = true;
        // Reset game state and restart
        reset_stats();
        updateDisplay();
        break;
    }
    arcada.getCanvas()->drawRGBBitmap(0, 0 , gameCover, 160,128);
    if (startCounter <= 50){
      arcada.getCanvas()->setTextColor(ARCADA_BLACK);
      arcada.getCanvas()->setCursor(2, 85);
      arcada.getCanvas()->println("Press");
      arcada.getCanvas()->setCursor(2, 95);
      arcada.getCanvas()->println("START!");
    }

    if (startCounter == 0){
      startCounter = 100;
    }
    
    arcada.blitFrameBuffer(0, 0, true);
    startCounter--;
    yield();
  }
}

// Function to show "You Win" screen
void showWinScreen() {
  arcada.getCanvas()->drawRGBBitmap(0, 0 , win_screen, 160,128);
  arcada.blitFrameBuffer(0, 0, true);

  while (true) {
    uint8_t buttonState = arcada.readButtons();
    if (buttonState & ARCADA_BUTTONMASK_A) {
      level1 = true;
      level2 = false;
      inGame = false;
      inCover = true;
      
      // Reset game state and restart
      reset_stats();
      updateDisplay();
      break;
    }
    yield();
  }
}

// Function to show the story between wininng level 1 and entering level 2
void startLevel2Screen() {
  arcada.getCanvas()->drawRGBBitmap(0, 0 , level_win1, 160,128);
  arcada.getCanvas()->setTextColor(ARCADA_BLACK);
  arcada.getCanvas()->setCursor(70, 115);
  arcada.getCanvas()->println("A to continue!");
  arcada.blitFrameBuffer(0, 0, true);
  while (true) {
    if (arcada.readButtons() & ARCADA_BUTTONMASK_A) {
      break;
    }
  }

  while (arcada.readButtons() & ARCADA_BUTTONMASK_A){}

  arcada.getCanvas()->drawRGBBitmap(0, 0 , level_win2, 160,128);
  arcada.getCanvas()->setTextColor(ARCADA_BLACK);
  arcada.getCanvas()->setCursor(70, 110);
  arcada.getCanvas()->println("A to continue!");
  arcada.blitFrameBuffer(0, 0, true);
  while (true) {
    uint8_t buttonState = arcada.readButtons();
    if (buttonState & ARCADA_BUTTONMASK_A) {
      level1 = false;
      level2 = true;
      // Reset game state and restart
      reset_stats();
      updateDisplay();
      break;
    }
    yield();
  }
}

// Function to show "GAME OVER" screen
void showGameOverScreen() {
  arcada.getCanvas()->fillScreen(ARCADA_BLACK);
  arcada.getCanvas()->setTextColor(ARCADA_RED);
  arcada.getCanvas()->setCursor(50, 40);
  arcada.getCanvas()->println("GAME OVER");
  arcada.getCanvas()->setCursor(30, 60);
  arcada.getCanvas()->println("Press A to Restart");
  arcada.blitFrameBuffer(0, 0, true);

  while (true) {
    uint8_t buttonState = arcada.readButtons();
    if (buttonState & ARCADA_BUTTONMASK_A) {
      // Reset game state and restart
      reset_stats();
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
  int buttonState = arcada.readButtons();

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

  // Check win condition
  if (characterPos >= 540) { // Adjusting the win condition for easier testing
    showWinScreen();
  }
}

// Controles the movement of the bomb after she is thrown
void bombMovement(){
  int buttonState = arcada.readButtons();
  // Throw item
  if ((buttonState & ARCADA_BUTTONMASK_B) && item->picked && level1) {
    isThrowing = true;
    item->picked = false;
    item->itemX += characterPos;
    if (bossActive){
      throwPower = 1;
      bouncePower = 0;
    } else {
      throwPower = 3;
    }
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
    item->itemX += throwVelocityX;
    item->itemY += throwVelocityY;

    throwVelocityY += gravity;

    if ((item->itemY + item->itemH) >= ground) {
      item->itemY = ground - item->itemH;

      if (!hasBounced) {
        throwVelocityY = -bouncePower;
        hasBounced = true;
      } else {
        throwVelocityX = 0;
        throwVelocityY = 0;
        wasThrown = false;
        bomb_expl = true;
        item->count--;
        item->active = false;
      }
    }
  }
}

// Movement of the companion
void moveCompanionInGame(){
  // save last direction of laser
  if (js_getDirection() == JS_RIGHT){
    laserDirectionX = laserX + 7;
    laserDirectionY = laserY+3;
    laser_pre_direction = JS_RIGHT;
  } else if (js_getDirection() == JS_LEFT){
    laserDirectionX = laserX-6;
    laserDirectionY = laserY+3;
    laser_pre_direction = JS_LEFT;
  } else if (js_getDirection() == JS_UP){
    laserDirectionX = laserX;
    laserDirectionY = laserY-6;
    laser_pre_direction = JS_UP;
  } else if (js_getDirection() == JS_DOWN){
    laserDirectionX = laserX;
    laserDirectionY = laserY+6;
    laser_pre_direction = JS_DOWN;
  }
  // Shoot laser when Joystick Button is pressed
  if ((js_getButton()) || laser_active){
    if (!laser_active){
      laser_direction = laser_pre_direction;
    }
    laser_active = true;

    if (laser_direction == JS_RIGHT){
      laserX += 2;
      if (laserX  > 170){
        laser_active = false;
      }
    }

    else if (laser_direction == JS_LEFT){
      laserX -= 2;
      if (laserX < -10){
        laser_active = false;
      }
    }

    else if (laser_direction == JS_UP){
      laserY -= 2;
      if (laserY < -10){
        laser_active = false;
      }
    }

    else {
      laserY += 2;
      if (laserY > 130){
        laser_active = false;
      }
    }
  }

  if (js_getDirection() == JS_RIGHT){
    moveCompanion(speedComp, 0);
    flyRight = true;
  }

   else if (js_getDirection() == JS_LEFT){
    moveCompanion(-speedComp, 0);
    flyRight = false;
  }

  else if (js_getDirection() == JS_UP){
    moveCompanion(0,-speedComp);
  }

  else if (js_getDirection() == JS_DOWN){
    moveCompanion(0,speedComp);
  }
}

// Function that controlls what should happend, when the game is on
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

  // Companion movement
  moveCompanionInGame();

  // Start item if not active
  if (!item->active && !bomb_expl){
    // nur einmal mit !item->init
    initItem();
  }

  // Flying object
  flyingItem();

  // Level 1, then we need the bomb movement
  if (level1){
    bombMovement();
  }

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
