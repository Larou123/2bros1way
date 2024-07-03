#ifndef OBSTACLE_H
#define OBSTACLE_H

// Global include
#include "globals.h"
#include "obstacle_img.h"

// Zeitsteuerung für die Animation
unsigned long lastFrameChangeH = 0;
int currentSpriteH = 0;

unsigned long lastFrameChangeF = 0;
int currentSpriteF = 0;

void obstacleCollisionL1(){
  if (damageAgain && !characterDamage && characterX + 26 >= kaktusX1-characterPos && characterX <= kaktusX1-characterPos + 17 && characterY + 32 >= ground-10){
    lives--;
    damageAgain = false;
  } else if (damageAgain && !characterDamage && characterX + 26 >= kaktusX2-characterPos && characterX <= kaktusX2-characterPos + 17 && characterY + 32 >= ground-10){
    lives--;
    damageAgain = false;
  }

  //water collision
  if (damageAgain && hydrantActive && currentSpriteH == 1){
    if (characterX+27 >= hydrantX-characterPos && characterX <= hydrantX+13-characterPos){
      lives--;
      damageAgain = false;
    }
  }
  if (damageCounter == 0){
    damageCounter = 60;
    damageAgain = true;
  } else {
    damageCounter--;
  }
}

void drawObstacleL1(){
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
  obstacleCollisionL1();
}

//-------Level2---------
void obstacleCollisionL2(){
  if (damageAgain && !characterDamage && characterX + 22 >= feuerX1-characterPos && characterX <= feuerX1-characterPos + 17 && characterY + 32 >= ground-10){
    lives--;
    damageAgain = false;
  } else if (damageAgain && !characterDamage && characterX + 22 >= feuerX2-characterPos && characterX <= feuerX2-characterPos + 17 && characterY + 32 >= ground-10){
    lives--;
    damageAgain = false;
  }

  //fire collision
  if (damageAgain && fackelActive && currentSpriteF == 1){
    if (characterX+29 >= fackelX-characterPos && characterX <= fackelX+13-characterPos){
      lives--;
      damageAgain = false;
    }
  }
  if (damageCounter == 0){
    damageCounter = 60;
    damageAgain = true;
  } else {
    damageCounter--;
  }
}

void drawObstacleL2(){
  //arcada.getCanvas()->fillTriangle(320-characterPos, ground+1, 340-characterPos,ground+1,330-characterPos,ground-10,ARCADA_BLACK);
  // KAKTUS
  arcada.getCanvas()->drawRGBBitmap(feuerX1-characterPos, ground-27, fire, fire_mask, 32, 32);
  arcada.getCanvas()->drawRGBBitmap(feuerX2-characterPos, ground-27, fire, fire_mask, 32, 32);
  
  // Fackel
  arcada.getCanvas()->drawRGBBitmap(fackelX-characterPos, ground-15,fire_obstacle, fire_obstacle_mask, 16, 16);
  if (fackelActive){
    unsigned long currentMillisF = millis();
    if (currentMillisF - lastFrameChangeF >= 700) {
      lastFrameChangeF = currentMillisF;
      currentSpriteF = (currentSpriteF + 1) % 3;
    }
    if (currentSpriteF == 0){
      arcada.getCanvas()->drawRGBBitmap(fackelX+3-characterPos, ground-20,pre_fire_spire,pre_fire_spire_mask,10,10);
    } else if (currentSpriteF == 1){
      arcada.getCanvas()->drawRGBBitmap(fackelX+3-characterPos, ground-10-100,fire_spire,fire_spire_mask,10,100);
    } else {
      fackelActive = false;
      fackelCounter = 45;
    }
  } 
  
  //für anim
  if (fackelCounter == 0){
    fackelActive = true;
  } else{
    fackelCounter--;
  }
  // comprove 
  obstacleCollisionL2();
}



#endif