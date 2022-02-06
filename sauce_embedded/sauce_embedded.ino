#include <Stepper.h>
#include "constants.h"
#include "wifi_functions.h"
#include "ultrasound.h"

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper stepper(STEPS_PER_ROT, STEPPER_PIN_1, STEPPER_PIN_2, STEPPER_PIN_3, STEPPER_PIN_4);
long timer;
long speed;

void setup() {
  Serial.begin(115200);
  setup_wifi();

  speed = long(http_get(QUERY_URL).toInt() * STEPPER_SPEED);
  stepper.setSpeed(speed);

  pinMode(PWM_PIN_1, OUTPUT);  // sets the pin as output
  pinMode(PWM_PIN_2, OUTPUT);  // sets the pin as output
  // Set duty cycle so stepper isn't going too hard
  analogWrite(PWM_PIN_1, DUTY_CYCLE);
  analogWrite(PWM_PIN_2, DUTY_CYCLE);
  timer = millis();
}

void loop() {
  stepper.step(STEPS_PER_LOOP);
  if (speed >= STEPPER_SPEED - 1) {
    bool stopped = isStopped(getUltrasoundReading());
    if (stopped) {
      http_get(STOPPED_URL);
      Serial.println("Reported stopped stirrer and texted user");
    }
  }
  if (millis() - timer > QUERY_PERIOD) {
    speed = long(http_get(QUERY_URL).toInt() * STEPPER_SPEED);
    stepper.setSpeed(speed);
    timer = millis();
  }
}
