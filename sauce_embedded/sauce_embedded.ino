#include <Stepper.h>
#include "constants.h"
#include "wifi_functions.h"
#include "ultrasound.h"

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper stepper(STEPS_PER_ROT, STEPPER_PIN_1, STEPPER_PIN_2, STEPPER_PIN_3, STEPPER_PIN_4);
unsigned long timer;
long speed;
bool stopDetected = false;
bool motorStopped;

void setStepperSpeed() {
  speed = long(http_get(QUERY_URL).toInt() * STEPPER_SPEED / 100);
  if (speed == 0) {
    motorStopped = true;
    stepper.setSpeed(1);
  } else {
    motorStopped = false;
    stepper.setSpeed(speed);
  }
  Serial.println(speed);
}

void setup() {
  Serial.begin(115200);
  setup_wifi();

  setStepperSpeed();

  pinMode(PWM_PIN_1, OUTPUT);  // sets the pin as output
  pinMode(PWM_PIN_2, OUTPUT);  // sets the pin as output
  // Set duty cycle so stepper isn't going too hard
  analogWrite(PWM_PIN_1, DUTY_CYCLE);
  analogWrite(PWM_PIN_2, DUTY_CYCLE);
  timer = millis();
}

void loop() {
  if (stopDetected) {
    stepper.step(STEPS_PER_LOOP);
    return;
  }

  if (!motorStopped) {
    stepper.step(STEPS_PER_LOOP);
  }

  if (speed >= STEPPER_SPEED - 1) {
//    Serial.println("Performing stop check");
    bool stopped = isStopped(getUltrasoundReading());
    if (stopped) {
      Serial.println("Reporting stopped stirrer and texted user");
      http_get(STOPPED_URL);
      // set duty cycle to full to continue stirring
      analogWrite(PWM_PIN_1, 255);
      analogWrite(PWM_PIN_2, 255);
      stopDetected = true;
      return;
    }
  }
 
  if (millis() - timer > QUERY_PERIOD) {
    Serial.println("Querying speed");
    setStepperSpeed();
    timer = millis();
  }
}
