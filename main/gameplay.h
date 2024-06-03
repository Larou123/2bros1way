#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include <Adafruit_Arcada.h>
#include <Adafruit_NeoPixel.h>

#include "globals.h"
#include "map.h"


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
  }

  if (isJumping && jumpCounter < 5){
    moveCharacter(0,5);
  }

  if (jumpCounter == 0){
      isJumping = false;
  }
  

  jumpCounter--;

  //move left
  if (buttonState & ARCADA_BUTTONMASK_LEFT) {
    //move left
    if (characterPos > 0){
      characterPos--;
    }
    moveCharacter(-speed, 0);
  }
  
  //move right
  if (buttonState & ARCADA_BUTTONMASK_RIGHT) {
    //move right
    if (characterPos < 100){
      characterPos++;
    }
    moveCharacter(speed, 0);
  }
}

void game(){
  // Show lives
  show_lives();

  // Update map
  drawMap();

  //test text
  arcada.getCanvas()->setCursor(2, 3);
  arcada.getCanvas()->setTextColor(ARCADA_BLACK);
  //arcada.getCanvas()->println("This is just a test!");

  // Start button presses
  if (arcada.readButtons() & ARCADA_BUTTONMASK_START){
    inGame = false;
    inMenu = true;
  }
  
  // Draw Character
  //drawCharacter();

  // Movement
  moveInGame();

  // Pick item
  pickItem();
}

#endif