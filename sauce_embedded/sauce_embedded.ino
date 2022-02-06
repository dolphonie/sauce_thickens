#include <Stepper.h>
#include "constants.h"
#include "wifi_functions.h"
#include "ultrasound.h"

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper stepper(STEPS_PER_ROT, STEPPER_PIN_1, STEPPER_PIN_2, STEPPER_PIN_3, STEPPER_PIN_4);

void setup() {
  Serial.begin(115200);
  // set the speed of the motor to 30 RPMs
  stepper.setSpeed(STEPPER_SPEED);
//  setup_wifi();
  
  String url = "https://sauce-thickens.loca.lt/api/interrupt";
//  http_post(url);
//  String response = http_post(url);
//  Serial.println(response);

  pinMode(PWM_PIN_1, OUTPUT);  // sets the pin as output
  pinMode(PWM_PIN_2, OUTPUT);  // sets the pin as output
  // Set duty cycle so stepper isn't going too hard
  analogWrite(PWM_PIN_1, DUTY_CYCLE);
  analogWrite(PWM_PIN_2, DUTY_CYCLE);
//  digitalWrite(PWM_PIN_1, HIGH);
//  digitalWrite(PWM_PIN_2, HIGH);
}

void loop() {
  stepper.step(STEPS_PER_LOOP);
  Serial.println(isStopped(getUltrasoundReading()));
}
