#ifndef BOSS_H
#define BOSS_H
#include "globals.h"
#include "boos_img.h"

// Sprites für die Attack 1 anim
const unsigned short *attack1RightSprites[] = {boss1_midanim_right, boss1_endanim_right};
const unsigned short *attack1LeftSprites[] = {boss1_midanim_left, boss1_endanim_left};
const unsigned char *attack1RightMasks[] = {boss1_midanim_right_mask, boss1_endanim_right_mask};
const unsigned char *attack1LeftMasks[] = {boss1_midanim_left_mask, boss1_endanim_left_mask};

// Zeitsteuerung für die Animation
unsigned long lastFrameChangeAt1 = 0;
int currentSpriteAt1 = 0;
void drawBoss(){
  //arcada.getCanvas()->fillRect(bossX-characterPos,bossY,bossW,bossH,ARCADA_BLACK);
  if (level1){
    if (boss1Attack){
      unsigned long currentMillisAt1 = millis();
      if (currentMillisAt1 - lastFrameChangeAt1 >= 300) {
        lastFrameChangeAt1 = currentMillisAt1;
        currentSpriteAt1 = (currentSpriteAt1 + 1) % 2; // Wechsel zwischen den Lauf-Sprites
        attack1_counter++;
        if (attack1_counter == 2){
          boss1Attack = false;
          attack1_counter = 30;
        }
      }

      if (bossRight){
        arcada.getCanvas()->drawRGBBitmap(bossX-characterPos+15, ground-40,attack1RightSprites[currentSpriteAt1] , attack1RightMasks[currentSpriteAt1], 50, 50);
      } else {
        arcada.getCanvas()->drawRGBBitmap(bossX-characterPos-32, ground-40, attack1LeftSprites[currentSpriteAt1] , attack1LeftMasks[currentSpriteAt1], 50, 50);
      }

    } else {
      if (bossRight){
          arcada.getCanvas()->drawRGBBitmap(bossX-characterPos, ground-32, boss1_right, boss1_right_mask, 32, 32);
      } else {
        arcada.getCanvas()->drawRGBBitmap(bossX-characterPos, ground-32, boss1_left, boss1_left_mask, 32, 32);
      }
    }
  }
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
  currentItemX = item->itemX-characterPos;
  if (currentBossX - (characterX+characterWidht) < 60){
    bossActive = true;
    leftLimit = 15;
    rightLimit = 145-characterWidht;
  }

  if (bossActive){
    if ((characterX) - currentBossX < 0){
    bossX -= bossSpeed;
    bossRight = false;

    } else if (characterX - currentBossX > 0 ) {
    bossX += bossSpeed;
    bossRight = true;
    }

    //kollision
    if (bomb_expl && !bossDamage && (abs(currentBossX - currentItemX) <= 20)){
      bossHP -= 30;
      bossDamage = true;
      if (bossHP <= 0){
        //wait till end bomb animation
        bossDamage = false;
        bossActive = false;
        bossHP = 100;
        showWinScreen();  
      }
    }

    if (!boss1Attack){
      attack1_counter--;
      if (attack1_counter == 0){
        boss1Attack = true;
      }
    }
      
   
  }
}


#endif