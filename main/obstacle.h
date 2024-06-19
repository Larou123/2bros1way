#ifndef OBSTACLE_H
#define OBSTACLE_H

// Global include
#include "globals.h"
#include "obstacle_img.h"

void drawObstacle(){
  //arcada.getCanvas()->fillTriangle(320-characterPos, ground+1, 340-characterPos,ground+1,330-characterPos,ground-10,ARCADA_BLACK);
  arcada.getCanvas()->drawRGBBitmap(160-characterPos, ground-27, kaktus, kaktus_mask, 27, 27);
  arcada.getCanvas()->drawRGBBitmap(320-characterPos, ground-20,hydrant, hydrant_mask, 20, 20);
}

#endif