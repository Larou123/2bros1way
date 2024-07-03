#ifndef MUSIC_H
#define MUSIC_H

#include "globals.h"

/*
Die Musik:
Title Derp Nugget (incompetech.com)
Licensed under Creative Commons: By Attribution 3.0
http://creativecommons.org/licenses/by/3.0/
*/


void timedInterruptCallback(void) {

 // play next sample
  wavStatus status = arcada.WavPlayNextSample();
// update playing state and hardware depending on wav playing status
  if (status == WAV_EOF) {
    arcada.timerStop();
    arcada.enableSpeaker(false);
    musicPlaying = false;
    musicDatei.close();
  } else {
    musicPlaying = true;
  }
}

  void loadMusic(){
   //open music file
    musicDatei = arcada.openFileByIndex("/music", 0, O_READ, "wav");
    if(!musicDatei){Serial.println("No sound present"); }
    Serial.println("Loading music");
    uint32_t sampleRate;
  // load wav information, enable speakers and set interrupt for sampling
    wavStatus status = arcada.WavLoad(musicDatei, &sampleRate);
    if ((status == WAV_LOAD) || (status == WAV_EOF)) {
      arcada.enableSpeaker(true);
      arcada.timerCallback(sampleRate, timedInterruptCallback);
    } else {
    Serial.println("Fatal error: Sound file corrupted.");
    }
    
  }





#endif