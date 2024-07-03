#include "globals.h"
#include "item_img.h"

Adafruit_Arcada arcada;
Adafruit_NeoPixel neopixels = Adafruit_NeoPixel(NEOPIXEL_COUNT, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);
unsigned long frameDelay = 100; // Zeit zwischen den Frames in Millisekunden

File musicDatei;
bool musicPlaying;

//GAME
bool level1 = false;
bool level2 = true;
bool level3 = false;
bool itemActive = false;

// MAP
int cloudX = 60;
int cloudY = 27;
int distanceCloud = 60;
int ground = 110;

// CHARACTER
int speed = 1;
int characterPos = 0;
int characterX = 20;
int characterY = ground - 32;
const int characterWidht = 32;
const int characterHeigh = 32;
int jumpCounter = 0;
bool isJumping = false;
bool wasJumping = false;
int lives = 5;
int rightLimit = 50;
int leftLimit = 20;
bool characterDamage = false;
// COMPANION
int speedComp = 1;
int companionX = 20;
int companionY = 12;
const int companionWidht = 40;
const int companionHeigh = 30;
int upLimit = 0;
int downLimit = 25;
bool flyRight = true;
int laserX = companionX + companionWidht;
int laserY = companionY+20;
bool laser_active = false;
Direction laser_direction = JS_NEUTRAL;

// GAME
bool inGame = false;
const char *menu_options[3] = {"Start", "Restart", "Quit"};
bool inMenu = false;
bool inCover = true;

// ITEM
bool isThrowing = false;
bool wasThrown = false;
// Variables for throw item physics
float throwVelocityX = 0;
float throwVelocityY = 0;
float throwPower = 3;
float bouncePower = 1;
bool hasBounced = false;
float currentItemX = 0;
bool bomb_expl = false;
int expl_count = 0;
bool itemCollision = false;

Item item__ = {
  .itemX = 0,
  .itemY = 0,
  .img = bomb_img,
  .mask = bomb_img_mask,
  .itemW = 0,
  .itemH = 0,
  .init = false,
  .active = false,
  .picked = false,
  .flying = false,
  .count = 3,
};

// ENEMY
int enemyW = 16;
int enemyH = 16;
float enemyX1 = 80;
float enemyX2 = 380;
int enemyY = ground - enemyH;
float enemySpeed = 0.5;
bool movingRight = true;
int distanceEnemy = 25;
int damageCounterEn = 60;
bool damageAgainEn = true;

// BOSS
int bossW = 30;
int bossH = 50;
float bossX = 530;
int bossY = ground - bossH;
float bossSpeed = 0.5;
bool bossRight = false;
bool bossActive = false;
float currentBossX = bossX;
float bossHP = 100;
bool bossDamage = false;
bool bossDamageLaser = false;
bool boss1Attack = false;
int attack1_counter = 30;

// OBSTACLES
int kaktusX1 = 150;
int kaktusX2 = 300;
int feuerX1 = 150;
int feuerX2 = 300;

int hydrantX = 230;
int damageCounter = 60;
bool damageAgain = true;
bool hydrantActive = false;
int hydrantCounter = 45;


int fackelX = 230;
bool fackelActive = false;
int fackelCounter = 45;