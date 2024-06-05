#ifndef MAP_H
#define MAP_H

// Global include
#include "globals.h"
#include "map_img.h"
#include "item.h"
#include "obstacle.h"

// Map size
#define MAP_WIDTH  320 // Example width, adjust to your map's actual width
#define MAP_HEIGHT 128 // Example height, adjust to your map's actual height

// Scrolling variables
float scrollX = 0;
float scrollSpeed = 5;

void drawCloud(){
  // Draws from image and tries to give movement
  arcada.getCanvas()->drawRGBBitmap(cloudX - scrollX, cloudY, cloud_img, cloud_mask, 40, 20);
}

// Draws map
void drawMap() {
  // Calculate scroll position
  scrollX = characterX - 80; // Adjust 80 to the character's starting position

  // Ensure scrolling boundaries
  if (scrollX < 0) {
    scrollX = 0;
  }
  if (scrollX > (MAP_WIDTH - 160)) { // 160 is the screen width
    scrollX = (MAP_WIDTH - 160);
  }

  // Draws from image
  arcada.getCanvas()->drawRGBBitmap(-scrollX, 0, map_img, MAP_WIDTH, MAP_HEIGHT);

  // Draw cloud
  drawCloud();

  // Draw item
  if (!itemPicked){
    drawItem(itemX - scrollX, itemY, itemW, itemH, itemC);
  }

  // Draw obstacle
  drawObstacle();
}

#endif
