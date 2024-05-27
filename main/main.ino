// pre pre pre pre beta, just draws a map and a trivial character

#include <Adafruit_Arcada.h>
#include <Adafruit_NeoPixel.h>

#define NEOPIXEL_PIN    8
#define NEOPIXEL_COUNT  5 

// Global variables
Adafruit_Arcada arcada;
Adafruit_NeoPixel neopixels = Adafruit_NeoPixel(NEOPIXEL_COUNT, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

//character variables
int characterX = 80;
int characterY = 84;
const int characterWidht = 4;
const int characterHeigh = 10;
int jumpCounter=0;
bool isJumping=false;


//menu variable
const char *menu_options[3] = {"Start", "Options", "Credits"};
bool inMenu = true;

//gameplay variable
bool inGame = false;

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
  neopixels.show();

  // Initialize display
  arcada.displayBegin();
  arcada.createFrameBuffer(ARCADA_TFT_WIDTH, ARCADA_TFT_HEIGHT);

  // Start with black screen
  arcada.getCanvas()->fillScreen(ARCADA_BLACK);

  // Draw the framebuffer to the screen
  arcada.blitFrameBuffer(0, 0, true, false);

  //map
  drawMap();
}

void loop() {
  // select
  if (inMenu){
    menu();
  } else if (inGame){
    game();
  }
  
  // Perform standard board functions
  yield();
}

void errorReporter(const char *error) {
  Serial.begin(9600);
  Serial.println(error);

  // Wait to keep USB connections, etc. running
  while (true) {
    yield();
  }
}

void drawMap() {
  // land
  arcada.display->fillRect(0, 64, 200, 74, ARCADA_GREEN);

  // sky
  arcada.display->fillRect(0, 0, 170, 94, ARCADA_CYAN);

  // obstacles
  //cada.display->fillRect(40, 15, 10, 10, ARCADA_RED); 
  //arcada.display->fillRect(70, 50, 10, 10, ARCADA_RED); 

  // border
  //arcada.display->drawRect(10, 10, 100, 60, ARCADA_WHITE);
}

void drawCharacter() {
  arcada.display->fillRect(characterX, characterY, characterWidht, characterHeigh, ARCADA_BLACK);
}

void moveCharacter(int nx, int ny) {
  // Ccear previous character position
  arcada.display->fillRect(characterX, characterY, characterWidht, characterHeigh, ARCADA_CYAN);

  // update character position
  characterX += nx;
  // set limits at the borders
  if (characterX < 0) characterX = 0;
  if (characterX > 156) characterX = 156;

    characterY += ny;
  // set limits at the borders
  if (characterY < 0) characterY = 0;
  if (characterY > 156) characterY = 156;

  // draw new position
  drawCharacter();
}

void moveInGame(){
  uint8_t buttonState = arcada.readButtons();
  //jump
  if (buttonState & ARCADA_BUTTONMASK_A && !isJumping) {
    //jump
    isJumping = true;
    jumpCounter = 10;
  }

  if (isJumping && jumpCounter > 5){
    moveCharacter(0,-5);
    if (!(buttonState & ARCADA_BUTTONMASK_LEFT) && !(buttonState & ARCADA_BUTTONMASK_RIGHT)){
      delay(35);
    }
  }

  if (isJumping && jumpCounter < 5){
    moveCharacter(0,5);
    if (!(buttonState & ARCADA_BUTTONMASK_LEFT) && !(buttonState & ARCADA_BUTTONMASK_RIGHT)){
      delay(35);
    }
  }

  if (jumpCounter == 0){
    isJumping = false;
  }

  jumpCounter--;

  //move right
  if (buttonState & ARCADA_BUTTONMASK_LEFT) {
    //move left
    moveCharacter(-1, 0);
    delay(35);
  }
  
  //move left
  if (buttonState & ARCADA_BUTTONMASK_RIGHT) {
    //move left
    moveCharacter(1, 0);
    delay(35);
  }
}
void game(){
  if (arcada.readButtons() & ARCADA_BUTTONMASK_START){
    inGame = false;
    inMenu = true;
  }

  drawCharacter();
  //test text
  arcada.display->setCursor(2, 3);
  arcada.display->setTextColor(ARCADA_BLACK);
  arcada.display->println("This is just a test!");

  //movement
  moveInGame();
}

void menu(){
  arcada.getCanvas()->fillScreen(ARCADA_WHITE);
  
  uint8_t menu_opt = arcada.menu(menu_options, 3, ARCADA_WHITE, ARCADA_BLACK);

  if (menu_opt == 0){
    inMenu = false;
    inGame = true;
    drawMap();
  }
}