#ifndef OBSTACLE_H
#define OBSTACLE_H

// Global include
#include "globals.h"

void drawObstacle(){
  arcada.getCanvas()->fillTriangle(120-characterPos, ground+1, 140-characterPos,ground+1,130-characterPos,ground-10,ARCADA_BLACK);
}

#endif