#ifndef BOSS_H
#define BOSS_H
#include "globals.h"


void drawBoss(){
  //arcada.getCanvas()->fillRect(bossX-characterPos,bossY,bossW,bossH,ARCADA_BLACK);
  arcada.getCanvas()->drawRGBBitmap(bossX-characterPos, ground-32, boss1, boss1_mask, 32, 32);
}

void showBossHP(){
  //draw bar
  if (bossActive){
    if (level1){
      arcada.getCanvas()->fillRoundRect(10,ground+8,140,8,8,ARCADA_BLACK);
      arcada.getCanvas()->fillRoundRect(10,ground+8,(bossHP/100)*140,8,8,ARCADA_ORANGE);
    } else{
       arcada.getCanvas()->fillRoundRect(10,ground+8,140,8,8,ARCADA_BLACK);
      arcada.getCanvas()->fillRoundRect(10,ground+8,(bossHP/100)*140,8,8,ARCADA_RED);
    }
  }  
}

void moveBoss(){
  currentBossX = bossX-characterPos;
  currentItemX = item->itemX;
  if (currentBossX - (characterX+characterWidht) < 60){
    bossActive = true;
    leftLimit = 15;
    rightLimit = 145-characterWidht;
  }

  if (bossActive){
    if ((characterX) - currentBossX < 0){
    bossX -= bossSpeed;

    } else if (characterX - currentBossX > 0 ) {
    bossX += bossSpeed;
    }

    //kollision
    if (bomb_expl && !bossDamage && (abs(currentBossX - currentItemX) <= 25)){
      bossHP -= 30;
      bossDamage = true;
      if (bossHP <= 0){
        bossDamage = false;
        bossActive = false;
        bossHP = 100;
        showWinScreen();
      }
    }                     
  }
}


#endif