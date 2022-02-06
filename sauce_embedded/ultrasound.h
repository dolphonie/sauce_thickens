#ifndef ULTRASOUND_H
#define ULTRASOUND_H
#include "Ultrasonic.h"
#include "constants.h"
Ultrasonic ultrasonic(ULTRASOUND_PIN);
int ultrasoundIndex = 0;
long ultrasoundBuffer[NUM_ULTRASOUND_SAMPLES];
bool bufferFilled = false;

long maxVal(long* arr) {
  long toRet = -9999;
  for (int i = 0; i < NUM_ULTRASOUND_SAMPLES; i++) {
    toRet = max(toRet, arr[i]);
  }
  return toRet;
}

long minVal(long *arr) {
  long toRet = 9999;
  for (int i = 0; i < NUM_ULTRASOUND_SAMPLES; i++) {
    toRet = min(toRet, arr[i]);
  }
  return toRet;
}

bool isStopped(long reading) {
  ultrasoundIndex++;
  ultrasoundIndex %= NUM_ULTRASOUND_SAMPLES;
  ultrasoundBuffer[ultrasoundIndex] = reading;
  if (ultrasoundIndex == 0) {
    bufferFilled = true;
  }
  if (bufferFilled) {
    long diff = maxVal(ultrasoundBuffer) - minVal(ultrasoundBuffer);
    return diff < MIN_CHANGE;
  } else {
    return false;
  }
}

long getUltrasoundReading() {
  long cm = ultrasonic.MeasureInCentimeters();
  return cm;
}

#endif
