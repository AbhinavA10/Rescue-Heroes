#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>
#include "pin_assignment.h"
#include "pitches.h"

void playStartupSound()
{
  pinMode(BUZZER, OUTPUT);
  int dur = 1000 / 8;
  float dur_between = dur * 1.3;
  tone(BUZZER, NOTE_C5, dur);
  delay(dur_between);
  noTone(BUZZER);
  tone(BUZZER, NOTE_E5, dur);
  delay(dur_between);
  noTone(BUZZER);
  tone(BUZZER, NOTE_F5, dur);
  delay(dur_between);
  noTone(BUZZER);
}


void playShutdownSound()
{
  pinMode(BUZZER, OUTPUT);
  int dur = 1000 / 8;
  float dur_between = dur * 1.3;
  tone(BUZZER, NOTE_F4, dur);
  delay(dur_between);
  noTone(BUZZER);
  tone(BUZZER, NOTE_E4, dur);
  delay(dur_between);
  noTone(BUZZER);
  tone(BUZZER, NOTE_C4, dur);
  delay(dur_between);
  noTone(BUZZER);
}
#endif
