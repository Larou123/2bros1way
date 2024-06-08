#ifndef ITEM_H
#define ITEM_H

#include "globals.h"
#include "item_img.h" // Einbinden der Bombenbilddaten und -masken

// Externe Deklaration der `arcada`-Instanz
extern Adafruit_Arcada arcada;

class Item {
public:
    virtual void draw(int x, int y) = 0;
};

class Bomb : public Item {
public:
    void draw(int x, int y) override {
        // Verkleinere das Item auf 16x16 und zeichne es mit der Maske
        arcada.getCanvas()->drawRGBBitmap(x, y, bomb_img, bomb_img_mask, 16, 16);
    }
};

#endif