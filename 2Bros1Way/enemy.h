#ifndef ENEMY_H
#define ENEMY_H
#include "globals.h"
#include "boos_img.h"

// Draw enemy depending of the level
void drawEnemy(){
  if (level1){ 
  arcada.getCanvas()->drawRGBBitmap(enemyX1-characterPos, enemyY, minienemy, minienemy_mask, 16, 16);
  if (!bossActive){
      arcada.getCanvas()->drawRGBBitmap(enemyX2-characterPos, enemyY, minienemy, minienemy_mask, 16, 16);

  }}
  else{
      arcada.getCanvas()->drawRGBBitmap(enemyX1-characterPos, enemyY, mini_enemy_lava, mini_enemy_lava_mask, 16, 16);
  if (!bossActive){
      arcada.getCanvas()->drawRGBBitmap(enemyX2-characterPos, enemyY, mini_enemy_lava, mini_enemy_lava_mask, 16, 16);

  }
  }
}

// Comprove if character has touched an enemy
void enemyCollision(){
  if (damageAgainEn && !isJumping && characterX + 25 >= enemyX1-characterPos && characterX <= enemyX1-characterPos + 5 && !bossActive){
    lives--;
    damageAgainEn = false;
  } else if (damageAgainEn && !isJumping && characterX + 25 >= enemyX2-characterPos && characterX <= enemyX2-characterPos + 5 && !bossActive){
    lives--;
    damageAgainEn = false;
  }

  if (damageCounterEn == 0){
    damageCounterEn = 60;
    damageAgainEn = true;
  } else {
    damageCounterEn--;
  }
}

// Changes the movement of the enemy, so it goes to left and right in a fixed distance
void moveEnemy(){
  if (level2){
    enemySpeed = 1;
  } else {
    enemySpeed = 0.5;
  }

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
  }
}

#endif