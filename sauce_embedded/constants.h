#ifndef constants
#define constants
// change this to the number of steps on your motor
const int STEPS_PER_ROT = 200;
const int STEPPER_SPEED = 30;

// stepper logic
const int STEPS_PER_LOOP = 5;

//stepper pins
const int STEPPER_PIN_1 = 14;
const int STEPPER_PIN_2 = 12;
const int STEPPER_PIN_3 = 13;
const int STEPPER_PIN_4 = 15;

// pwm pins
const int PWM_PIN_1 = 16;
const int PWM_PIN_2 = 2;

// ultrasound constants
const int ULTRASOUND_PIN = 0;
const int MIN_CHANGE = 13;
const int NUM_ULTRASOUND_SAMPLES = 40;

//duty cycle
const int DUTY_CYCLE = 96; // from 0 to 255


// Wifi constants
char NETWORK[] = "stratus";  // SSID for Wifi Network
char PASSWORD[] = "jeremysux"; // Password for Wifi Network

String QUERY_URL = "http://sauce-thickens.loca.lt/api/status";
String STOPPED_URL = "http://sauce-thickens.loca.lt/api/interrupt";

const unsigned long QUERY_PERIOD = 5000;

#endif
