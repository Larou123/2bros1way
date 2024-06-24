#ifndef ITEM_H
#define ITEM_H

#include "globals.h"
#include "item_img.h" // Einbinden der Bombenbilddaten und -masken


const unsigned short *explosion[] = {bombexplosion1,bombexplosion2,bombexplosion3,bombexplosion4};
const unsigned char *explosion_mask[] = {bombexpl1_mask,bombexpl2_mask,bombexpl3_mask,bombexpl4_mask};
// Zeitsteuerung für die Animation
unsigned long lastFrameChangeIt = 0;


void drawItem(int x, int y) {
  if (item->flying && item->itemY == 20){
    //bomb, we have to adjust it, we have to save the img to item->img, like down
    arcada.getCanvas()->drawRGBBitmap(x, y,fly_bomb, fly_bomb_mask, 20, 20);
  } else{
    arcada.getCanvas()->drawRGBBitmap(x, y, item->img, item->mask, item->itemW, item->itemH);
  }
}

void initItem(){
  if (level1){
    item->itemX = 170 + characterPos;
    item->itemY = 20;
    item->img = bomb_img;
    item->mask = bomb_img_mask;
    item->itemH = 16;
    item->itemW = 16;
    item->init = true;
    item->active = true;
    item->flying = true;
  }
  else if(level2){
    level2 = false;
  }
  else if(level3){
    level3 = false;
  }
}
void pickItem() {
    int itemTmp = item->itemX - characterPos;
    if (!item->picked && !item->flying && item->init) {
        if ((-32 <= characterX - itemTmp) && ((characterX - itemTmp) <= 32) && (arcada.readButtons() & ARCADA_BUTTONMASK_DOWN)) {
            item->picked = true;
        }
    }
}

void flyingItem(){
  // item flies
  if (item->flying){
    if (!itemCollision){
      item->itemX -= 1;
      if (item->itemX-characterPos <= -50){
        item->active = false;
      }
    }
    // item falls
    else {
      if (item->itemY < ground - 16){
        item->itemY += 2;
      } else {
        item->flying = false;
        itemCollision = false;
      }     
    }
  }
}

void bomb_explode(){
  if (bomb_expl){
    unsigned long currentMillis = millis();
    if (currentMillis - lastFrameChangeIt >= 200) {
      lastFrameChangeIt = currentMillis;
      arcada.getCanvas()->drawRGBBitmap(item->itemX-characterPos, item->itemY, explosion[expl_count], explosion_mask[expl_count], 25, 25);
      expl_count++;
    }

    if (expl_count == 3){
      expl_count = 0;
      bomb_expl = false;
      bossDamage = false;
      //if boss killed, game win screen
      if (bossHP <= 0){
        showWinScreen();  
      }
    }
  }
}
#endif