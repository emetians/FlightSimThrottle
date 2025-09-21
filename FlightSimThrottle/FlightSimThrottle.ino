#include "Joystick.h"

// PIN SETUP
#define PIN_AXIS_THROTTLE_R A1
#define PIN_AXIS_THROTTLE_L A2
#define PIN_AXIS_SPOILER A0
#define PIN_BUTTON_ENC 2
#define PIN_ENC_A 3
#define PIN_ENC_B 4
#define PIN_SWITCH_LEFT 5
#define PIN_SWITCH_RIGHT 6
#define PIN_BUTTON_THROTTLE 7


void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_AXIS_THROTTLE_R, INPUT);
  pinMode(PIN_AXIS_THROTTLE_L, INPUT);
  pinMode(PIN_AXIS_SPOILER, INPUT);
  pinMode(PIN_BUTTON_ENC, INPUT_PULLUP);
  pinMode(PIN_ENC_A, INPUT_PULLUP);
  pinMode(PIN_ENC_B, INPUT_PULLUP);
  pinMode(PIN_SWITCH_LEFT, INPUT_PULLUP);
  pinMode(PIN_SWITCH_RIGHT, INPUT_PULLUP);
  pinMode(PIN_BUTTON_THROTTLE, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int rightThrottleValue = analogRead(PIN_AXIS_THROTTLE_R); // max: 373
  int leftThrottleValue = 1023 - analogRead(PIN_AXIS_THROTTLE_L); // 1023 - readed value means revering axis, max: 448
  int spoilerValue = 1023 - analogRead(PIN_AXIS_SPOILER); // max: 645
  bool encButtonState = digitalRead(PIN_BUTTON_ENC); // when pressed 0
  bool encAState = digitalRead(PIN_ENC_A);
  bool encBState = digitalRead(PIN_ENC_A);
  bool leftSwitchState = digitalRead(PIN_SWITCH_LEFT); // when up 1
  bool rightSwitchState = digitalRead(PIN_SWITCH_RIGHT); // when up 1
  bool throttleButtonState = digitalRead(PIN_BUTTON_THROTTLE); // when pressed 0

  char message[1000];
  sprintf(message, "RT: %d, LT: %d, SP: %d, encBt: %d, encA: %d, encB:%d, LSw: %d, RSw: %d, thBT: %d\n",
                    rightThrottleValue, leftThrottleValue, spoilerValue, encButtonState, encAState,
                    encBState, leftSwitchState, rightSwitchState, throttleButtonState);
  Serial.print(message);
  delay(500);
}
