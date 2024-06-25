#ifndef MAP_H
#define MAP_H

// Global include
#include "globals.h"
#include "map_img.h"
#include "item.h"
#include "obstacle.h"
// 160 * 128


void drawCloud(){
  // Draws from image and tries to give movement
  arcada.getCanvas()->drawRGBBitmap(cloudX-characterPos, cloudY , cloud_img,cloud_mask,40,20);
}

// Draws map
void drawMap() {
  // Draws from image
  if (level1){
    arcada.getCanvas()->drawRGBBitmap(0, 0 , background1, 160,81);
    arcada.getCanvas()->drawRGBBitmap(0-characterPos, 81 , ground1, 320,48);
    arcada.getCanvas()->drawRGBBitmap(320-characterPos, 81 , ground1, 320,48);
    // Draw cloud
    drawCloud();
    // Draw obstacle
    drawObstacleL1();
  } else if(level2){
    arcada.getCanvas()->drawRGBBitmap(0, 0 , background2, 160,81);
    arcada.getCanvas()->drawRGBBitmap(0-characterPos, 81 , ground2, 320,48);
    arcada.getCanvas()->drawRGBBitmap(320-characterPos, 81 , ground2, 320,48);
  }
  
  // Draw item
  if (!item->picked && item->active){
    drawItem(item->itemX-characterPos,item->itemY);
  }
  
  
}

#endif