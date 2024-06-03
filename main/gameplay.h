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

// Movement during game
void moveInGame(){
  uint8_t buttonState = arcada.readButtons();
  // --------------------------------- Jump --------------------------------------------
   if (buttonState & ARCADA_BUTTONMASK_A && !wasJumping && !isJumping) {
    isJumping = true;
    jumpCounter = 10;
  }
  wasJumping = buttonState & ARCADA_BUTTONMASK_A;


  if (isJumping && jumpCounter > 5){
    moveCharacter(0,-5);
  }

  if (isJumping && jumpCounter < 5){
    moveCharacter(0,5);
  }

  if (jumpCounter == 0){
      isJumping = false;
  }
  

  jumpCounter--;

  // --------------------------------- To Left ---------------------------------
  if (buttonState & ARCADA_BUTTONMASK_LEFT) {
    //move left
    if (characterPos > 0){
      characterPos--;
    }
    moveCharacter(-speed, 0);
  }
  
  // --------------------------------- To Right ---------------------------------
  if (buttonState & ARCADA_BUTTONMASK_RIGHT) {
    //move right
    if (characterPos < 100){
      characterPos++;
    }
    moveCharacter(speed, 0);
  }

  // --------------------------------- Throw item ---------------------------------
  if ((buttonState & ARCADA_BUTTONMASK_B) && itemPicked) {
    isThrowing = true;
    itemCounter = 5;
    itemPicked = false;
  }

  // Lineal movement
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
}

void game(){
  // Show lives
  show_lives();

  //test text
  arcada.getCanvas()->setCursor(2, 3);
  arcada.getCanvas()->setTextColor(ARCADA_BLACK);
  //arcada.getCanvas()->println("This is just a test!");

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