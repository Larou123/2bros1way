#ifndef ITEM_H
#define ITEM_H

#include "globals.h"
#include "item_img.h" // Einbinden der Bombenbilddaten und -masken


const unsigned short *explosion[] = {bombexplosion1,bombexplosion2,bombexplosion3,bombexplosion4};
const unsigned char *explosion_mask[] = {bombexpl1_mask,bombexpl2_mask,bombexpl3_mask,bombexpl4_mask};
// Zeitsteuerung für die Animation
unsigned long lastFrameChangeIt = 0;

void drawItem(int x, int y) {
  arcada.getCanvas()->drawRGBBitmap(x, y, bomb_img, bomb_img_mask, 16, 16);
}

void pickItem() {
    int itemTmp = itemX - characterPos;
    if (!itemPicked) {
        if ((-32 <= characterX - itemTmp) && ((characterX - itemTmp) <= 32) && (arcada.readButtons() & ARCADA_BUTTONMASK_DOWN)) {
            itemPicked = true;
        }
    }
}

void bomb_explode(){
  if (bomb_expl){
    item_active = false;
    unsigned long currentMillis = millis();
    if (currentMillis - lastFrameChangeIt >= 200) {
      lastFrameChangeIt = currentMillis;
      arcada.getCanvas()->drawRGBBitmap(itemX-characterPos, itemY, explosion[expl_count], explosion_mask[expl_count], 25, 25);
      expl_count++;
    }

    if (expl_count == 3){
      expl_count = 0;
      bomb_expl = false;
    }
  }
}
#endif