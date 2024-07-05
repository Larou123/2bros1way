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

// Sprites für die Attack 1 anim
const unsigned short *attack2RightSprites[] = {fourArms_animation_right, fourArms_canon_right,fourArms_right};
const unsigned short *attack2LeftSprites[] = {fourArms_animation_left, fourArms_canon_left,fourArms_left};
const unsigned char *attack2RightMasks[] = {fourArms_animation_right_mask, fourArms_canon_right_mask,fourArms_right_mask};
const unsigned char *attack2LeftMasks[] = {fourArms_animation_left_mask, fourArms_canon_left_mask,fourArms_left_mask};

// Zeitsteuerung für die Animation
unsigned long lastFrameChangeAt2 = 0;
int currentSpriteAt2 = 0;
int fireCanonSpeed = 1;
bool fireCanonRight = bossRight;

void drawFireCanon(){
  if (fireCanon){
    if (bossHP < 66){
      fireCanonSpeed = 2;
    } else if (bossHP < 33){
      fireCanonSpeed = 3;
    }
    if (fireCanonRight){
      fireCanonX += fireCanonSpeed;
      if (fireCanonX+30 > 160){
        fireCanon = false;
        boss2Attack = false;
        attack2_counter = 30;
      }
      arcada.getCanvas()->drawRGBBitmap(fireCanonX, ground-32,fire_canon_right, fire_canon_right_mask, 27, 10);
    } else {
      fireCanonX -= fireCanonSpeed;
      if (fireCanonX-3 < 0){
        fireCanon = false;
        boss2Attack = false;
        attack2_counter = 50;
      }
      arcada.getCanvas()->drawRGBBitmap(fireCanonX, ground-32,fire_canon_left, fire_canon_left_mask, 27, 10);
    }

  }
}
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
          characterDamage = false;
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
  } else if(level2){
    if (boss2Attack && !fireCanon){
      unsigned long currentMillisAt2 = millis();
      if (currentMillisAt2 - lastFrameChangeAt2 >= 300) {
        lastFrameChangeAt2 = currentMillisAt2;
        currentSpriteAt2 = (currentSpriteAt2 + 1) % 3; // Wechsel zwischen den Lauf-Sprites
        attack2_counter++;

        if ((currentSpriteAt2 + 1) == 3){
          characterDamage = false;

          fireCanon = true;
          fireCanonRight = bossRight;
          if (fireCanonRight){
            fireCanonX = bossX-characterPos+30;
          } else {
            fireCanonX = bossX-characterPos-17;
          }
        }
      }

      if (bossRight){
        fireCanonX = bossX-characterPos+30;
        arcada.getCanvas()->drawRGBBitmap(fireCanonX, ground-32,fire_canon_right , fire_canon_right_mask, 27, 10);
        arcada.getCanvas()->drawRGBBitmap(bossX-characterPos, ground-40,attack2RightSprites[currentSpriteAt2] , attack2RightMasks[currentSpriteAt2], 40, 40);
      } else {
        fireCanonX = bossX-characterPos-17;
        arcada.getCanvas()->drawRGBBitmap(fireCanonX, ground-32,fire_canon_left , fire_canon_left_mask, 27, 10);
        arcada.getCanvas()->drawRGBBitmap(bossX-characterPos, ground-40, attack2LeftSprites[currentSpriteAt2] , attack2LeftMasks[currentSpriteAt2], 40, 40);
      }

    } else {
      if (bossRight){
          arcada.getCanvas()->drawRGBBitmap(bossX-characterPos, ground-40, fourArms_right, fourArms_right_mask, 40, 40);
      } else {
        arcada.getCanvas()->drawRGBBitmap(bossX-characterPos, ground-40, fourArms_left, fourArms_left_mask, 40, 40);
      }
    }
    if (fireCanon && bossActive){
      drawFireCanon();
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

void boss1At(){
  currentBossX = bossX-characterPos;
  if (boss1Attack){
    if (bossRight){
      if (!characterDamage && (currentBossX + 50 + 10 >= characterX && currentBossX < characterX) && characterY > ground-32-5){
        lives--;
        characterDamage = true;
      }
    } else{
      if (!characterDamage && (characterX+32 >= currentBossX - 26 && characterX < currentBossX) && characterY > ground-32-5){
        lives--;
        characterDamage = true;
      }
    }
  }
}

void boss2At(){
  if (boss2Attack){
    if (bossRight){
      if (!characterDamage && (abs(fireCanonX - characterX) <= 15) && characterY + 35 > ground-fireCanonY){
        lives--;
        characterDamage = true;
      }
    } else{
      if (!characterDamage && (abs(fireCanonX - characterX) <= 15) && characterY + 35 > ground-fireCanonY){
        lives--;
        characterDamage = true;
      }
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

    //kollision für level1
    if (level1){
      if (bomb_expl && !bossDamage && (abs(currentBossX - currentItemX) <= 15)){
      bossHP -= 30;
      bossDamage = true;
    }
    boss1At();
    if (!boss1Attack){
      attack1_counter--;
      if (attack1_counter == 0){
        boss1Attack = true;
      }
    }
    } else {
      if (attackDamage && !bossDamage && ( (abs(currentBossX - (characterX + 30)) <= 15) | (abs((currentBossX + 40) - characterX) <= 15) )){
        bossHP -= 20;
        bossDamage = true;
      }
      boss2At();
      if (!boss2Attack){
      attack2_counter--;
      if (attack2_counter == 0){
        boss2Attack = true;
      }
    }
    }
  }
}
#endif