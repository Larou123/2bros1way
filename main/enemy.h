#ifndef ENEMY_H
#define ENEMY_H
#include "globals.h"
#include "boos_img.h"

void drawEnemy(){
  //arcada.getCanvas()->fillRect(enemyX-characterPos,enemyY,enemyW,enemyH,ARCADA_BLACK);
  arcada.getCanvas()->drawRGBBitmap(enemyX-characterPos, enemyY-16, minienemy, minienemy_mask, 16, 16);
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