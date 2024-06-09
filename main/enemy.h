#ifndef ENEMY_H
#define ENEMY_H
#include "globals.h"

void drawEnemy(){
  arcada.getCanvas()->fillRect(enemyX-characterPos,enemyY,enemyW,enemyH,ARCADA_BLACK);
}

void moveEnemy(){
  if (movingRight){
    enemyX += enemySpeed;
  } else{
    enemyX -= enemySpeed;
  }

  distanceEnemy--;

  if (distanceEnemy == 0){
    movingRight = !movingRight;
    distanceEnemy = 25;
  }
}

#endif