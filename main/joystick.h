#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "globals.h"


// var
const int xPin = A0; // X-axis of joystick connected to analog pin A2
const int yPin = A1; // Y-axis of joystick connected to analog pin A1
const int buttonPin = 5; // Button of joystick connected to digital pin 5
const int neutral = 512;
//! Initializes joystick.

void js_init(){
  pinMode(buttonPin, INPUT_PULLUP);
}

//! Returns direction of the joystick.
Direction js_getDirection(void){
	int horizontal = analogRead(xPin);
	int vertical = analogRead(yPin);

	if (horizontal < neutral - 100) {
    return JS_LEFT;
  } else if (horizontal > neutral + 100) {
    return JS_RIGHT;
  } else if (vertical < neutral - 100) {
    return JS_UP;
  } else if (vertical > neutral + 100) {
    return JS_DOWN;
  } else {
    return JS_NEUTRAL;
  }
}

//! Returns if joystick is pressed.
bool js_getButton(void){
  return digitalRead(buttonPin) == LOW;
}

#endif