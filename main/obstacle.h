#ifndef OBSTACLE_H
#define OBSTACLE_H

// Global include
#include "globals.h"
#include "obstacle_img.h"

// Zeitsteuerung für die Animation
unsigned long lastFrameChangeH = 0;
int currentSpriteH = 0;

void obstacleCollision(){
  if (damageAgain && !characterDamage && characterX + 26 >= kaktusX1-characterPos && characterX <= kaktusX1-characterPos + 17 && characterY + 32 >= ground-10){
    lives--;
    damageAgain = false;
  } else if (damageAgain && !characterDamage && characterX + 26 >= kaktusX2-characterPos && characterX <= kaktusX2-characterPos + 17 && characterY + 32 >= ground-10){
    lives--;
    damageAgain = false;
  }

  //water collision
  if (hydrantActive && currentSpriteH == 1){
    
  }
  if (damageCounter == 0){
    damageCounter = 60;
    damageAgain = true;
  } else {
    damageCounter--;
  }
}

void drawObstacle(){
  //arcada.getCanvas()->fillTriangle(320-characterPos, ground+1, 340-characterPos,ground+1,330-characterPos,ground-10,ARCADA_BLACK);
  // KAKTUS
  arcada.getCanvas()->drawRGBBitmap(kaktusX1-characterPos, ground-27, kaktus, kaktus_mask, 27, 27);
  arcada.getCanvas()->drawRGBBitmap(kaktusX2-characterPos, ground-27, kaktus, kaktus_mask, 27, 27);
  
  // HYDRANT
  arcada.getCanvas()->drawRGBBitmap(hydrantX-characterPos, ground-15,hydrant, hydrant_mask, 20, 20);
  if (hydrantActive){
    unsigned long currentMillisH = millis();
    if (currentMillisH - lastFrameChangeH >= 700) {
      lastFrameChangeH = currentMillisH;
      currentSpriteH = (currentSpriteH + 1) % 3;
    }
    if (currentSpriteH == 0){
      arcada.getCanvas()->drawRGBBitmap(hydrantX+1-characterPos, ground-14,pre_waterspire,pre_waterspire_mask,18,8);
    } else if (currentSpriteH == 1){
      arcada.getCanvas()->drawRGBBitmap(hydrantX+1-characterPos, ground-6-100,waterspire,waterspire_mask,20,100);
    } else {
      hydrantActive = false;
      hydrantCounter = 45;
    }
  } 
  
  //für anim
  if (hydrantCounter == 0){
    hydrantActive = true;
  } else{
    hydrantCounter--;
  }
  // comprove 
  obstacleCollision();
}


#endif