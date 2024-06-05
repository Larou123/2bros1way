#ifndef OBSTACLE_H
#define OBSTACLE_H

// Global include
#include "globals.h"

void drawObstacle(){
  arcada.getCanvas()->fillTriangle(320-characterPos, ground+1, 340-characterPos,ground+1,330-characterPos,ground-10,ARCADA_BLACK);
}

#endif