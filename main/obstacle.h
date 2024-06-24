#ifndef OBSTACLE_H
#define OBSTACLE_H

// Global include
#include "globals.h"
#include "obstacle_img.h"

void obstacleCollision(){
  if (damageAgain && !characterDamage && characterX + 26 >= kaktusX1-characterPos && characterX <= kaktusX1-characterPos + 17 && characterY + 32 >= ground-10){
    lives--;
    damageAgain = false;
  } else if (damageAgain && !characterDamage && characterX + 26 >= kaktusX2-characterPos && characterX <= kaktusX2-characterPos + 17 && characterY + 32 >= ground-10){
    lives--;
    damageAgain = false;
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
  arcada.getCanvas()->drawRGBBitmap(hydrantX-characterPos, ground-20,hydrant, hydrant_mask, 20, 20);

  // comprove 
  obstacleCollision();
}


#endif