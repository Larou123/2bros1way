#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include <Adafruit_Arcada.h>
#include <Adafruit_NeoPixel.h>

#include "globals.h"



void moveInGame(){
  uint8_t buttonState = arcada.readButtons();
  //jump
   if (buttonState & ARCADA_BUTTONMASK_A && !wasJumping && !isJumping) {
    //jump
    isJumping = true;
    jumpCounter = 10;
  }
  wasJumping = buttonState & ARCADA_BUTTONMASK_A;


  if (isJumping && jumpCounter > 5){
    moveCharacter(0,-5);
    if (!(buttonState & ARCADA_BUTTONMASK_LEFT) && !(buttonState & ARCADA_BUTTONMASK_RIGHT)){
      delay(35);
    }
  }

  if (isJumping && jumpCounter < 5){
    moveCharacter(0,5);
    if (!(buttonState & ARCADA_BUTTONMASK_LEFT) && !(buttonState & ARCADA_BUTTONMASK_RIGHT)){
      delay(35);
    }
  }

  if (jumpCounter == 0){
    isJumping = false;
  }

  jumpCounter--;

  //move right
  if (buttonState & ARCADA_BUTTONMASK_LEFT) {
    //move left
    moveCharacter(-1, 0);
    delay(35);
  }
  
  //move left
  if (buttonState & ARCADA_BUTTONMASK_RIGHT) {
    //move left
    moveCharacter(1, 0);
    delay(35);
  }
}

void game(){
  //lives
  show_lives();

  //test text
  arcada.display->setCursor(2, 3);
  arcada.display->setTextColor(ARCADA_BLACK);
  arcada.display->println("This is just a test!");

  //start button
  if (arcada.readButtons() & ARCADA_BUTTONMASK_START){
    inGame = false;
    inMenu = true;
  }
  
  drawCharacter();
  
  //movement
  moveInGame();
}


#endif