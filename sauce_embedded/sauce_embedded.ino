#include <Stepper.h>
#include "constants.h"
#include "wifi_functions.h"

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper stepper(STEPS, STEPPER_PIN_1, STEPPER_PIN_2, STEPPER_PIN_3, STEPPER_PIN_4);

void setup() {
  Serial.begin(115200);
  // set the speed of the motor to 30 RPMs
  stepper.setSpeed(60);
  setup_wifi();
  Serial.println("testing");
  String url = "http://jsonplaceholder.typicode.com/users/1";
  String response = http_get(url);
  Serial.println(response);
}

void loop() {
  Serial.println("clockwise");
  stepper.step(STEPS);
  delay(500);

  // step one revolution in the other direction:
  Serial.println("counterclockwise");
  stepper.step(-STEPS);
  delay(500);
}
