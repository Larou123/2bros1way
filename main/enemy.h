#ifndef ENEMY_H
#define ENEMY_H
#include "globals.h"
#include "boos_img.h"

void drawEnemy(){
  //arcada.getCanvas()->fillRect(enemyX-characterPos,enemyY,enemyW,enemyH,ARCADA_BLACK);
  arcada.getCanvas()->drawRGBBitmap(enemyX1-characterPos, enemyY, minienemy, minienemy_mask, 16, 16);
  if (!bossActive){
      arcada.getCanvas()->drawRGBBitmap(enemyX2-characterPos, enemyY, minienemy, minienemy_mask, 16, 16);

  }
}

void enemyCollision(){
  if (!characterDamage && !isJumping && characterX + 25 >= enemyX1-characterPos && characterX <= enemyX1-characterPos + 5){
    lives--;
    characterDamage = true;
  } else if (!characterDamage && !isJumping && characterX + 25 >= enemyX2-characterPos && characterX <= enemyX2-characterPos + 5){
    lives--;
    characterDamage = true;
  }
}

void moveEnemy(){
  if (movingRight){
    enemyX1 += enemySpeed;
    enemyX2 += enemySpeed;
  } else{
    enemyX1 -= enemySpeed;
    enemyX2 -= enemySpeed;
  }

  enemyCollision();

  distanceEnemy--;

  if (distanceEnemy == 0){
    movingRight = !movingRight;
    distanceEnemy = 25;
    characterDamage = false;
  }
}

#endif