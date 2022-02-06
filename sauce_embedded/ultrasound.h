#ifndef ULTRASOUND_H
#define ULTRASOUND_H
#include "Ultrasonic.h"
#include "constants.h"
Ultrasonic ultrasonic(ULTRASOUND_PIN);
int ultrasoundIndex = 0;
float ultrasoundBuffer[NUM_ULTRASOUND_SAMPLES];
bool bufferFilled = false;

float maxVal(float* arr) {
  float toRet = -9999;
  for (int i = 0; i < sizeof(arr); i++) {
    toRet = max(toRet, arr[i]);
  }
  return toRet;
}

float minVal(float* arr) {
  float toRet = 9999;
  for (int i = 0; i < sizeof(arr); i++) {
    toRet = min(toRet, arr[i]);
  }
  return toRet;
}

bool isStopped(float reading) {
  ultrasoundIndex++;
  ultrasoundIndex %= NUM_ULTRASOUND_SAMPLES;
  ultrasoundBuffer[ultrasoundIndex] = reading;
  float arrMax = maxVal(ultrasoundBuffer);
  float arrMin = minVal(ultrasoundBuffer);
  if (ultrasoundIndex == 0) {
    bufferFilled = true;
  }
  if (bufferFilled) {
    float diff = maxVal(ultrasoundBuffer) - minVal(ultrasoundBuffer);
    Serial.println(diff);
    return diff < MIN_CHANGE;
  } else {
    return false;
  }
}

float getUltrasoundReading() {
  return ultrasonic.MeasureInCentimeters();
}

#endif
