#ifndef OBSTACLE_H
#define OBSTACLE_H

// Global include
#include "globals.h"

void drawObstacle(){
  arcada.getCanvas()->fillTriangle(120-characterPos, ground, 140-characterPos,ground,130-characterPos,ground-10,ARCADA_BLACK);
}

#endif