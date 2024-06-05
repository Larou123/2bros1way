#ifndef ITEM_H
#define ITEM_H

// Global include
#include "globals.h"
#include "character.h"

void drawItem(int x, int y, int w, int h, int color){
    arcada.getCanvas()->fillRect(x,y,w,h,color);
}

void pickItem(){
  int itemTmp = itemX - characterPos;
  if (!itemPicked){
    if (( -32 <= characterX - itemTmp) && ((characterX - itemTmp) <= 32) && (arcada.readButtons() & ARCADA_BUTTONMASK_DOWN)){
        itemPicked = true;    
    }
  }
}
#endif