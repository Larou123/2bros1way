#include "globals.h"
#include "character.h"
#include "map.h"
#include "gameplay.h"
#include "menu.h"
#include "char.h"
#include "map_img.h"
#include "item.h" // Hinzufügen der Item-Definitionen
#include "obstacle.h"

void setup() {
    // Initialize Arcada library
    if (!arcada.arcadaBegin()) {
        errorReporter("Fatal error: Arcada library failed.");
    }

    // Enable backlight
    arcada.setBacklight(255);

    // Initialize NeoPixels
    neopixels.begin();
    neopixels.clear();
    neopixels.setBrightness(50);

    // Initialize display
    arcada.displayBegin();
    arcada.createFrameBuffer(ARCADA_TFT_WIDTH, ARCADA_TFT_HEIGHT);

    // Draw map
    updateDisplay();

    // Set current item to Bomb
    currentItem = new Bomb();
}

void loop() {
    // Mode selection
    if (inMenu) {
        menu();
    } else if (inGame) {
        game();
    }

    // Perform standard board functions
    yield();

    // Beispiel: Zeichnen des aktuellen Items
    if (!itemPicked) {
        drawItem(itemX - characterPos, itemY, itemW, itemH, itemC);
    }
}

void errorReporter(const char *error) {
    Serial.begin(9600);
    Serial.println(error);

    // Wait to keep USB connections, etc. running
    while (true) {
        yield();
    }
}