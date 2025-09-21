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

volatile byte aFlag = 0; 
volatile byte bFlag = 0; 
volatile byte encoderPos = 0; 
volatile byte oldEncPos = 0;
volatile byte reading = 0;

bool lastA;
int test = 0;
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
  lastA = digitalRead(PIN_ENC_A);
}

void loop() {
  // put your main code here, to run repeatedly:
  int thRightVal = analogRead(PIN_AXIS_THROTTLE_R); // max: 373
  int thLeftVal = 1023 - analogRead(PIN_AXIS_THROTTLE_L); // 1023 - readed value means revering axis, max: 448
  int spVal = 1023 - analogRead(PIN_AXIS_SPOILER); // max: 645
  bool butEncSt = digitalRead(PIN_BUTTON_ENC); // when pressed 0
  bool encASt = digitalRead(PIN_ENC_A);
  bool encBSt = digitalRead(PIN_ENC_A);;
  bool swLeftSt = digitalRead(PIN_SWITCH_LEFT); // when up 1
  bool swRightSt = digitalRead(PIN_SWITCH_RIGHT); // when up 1
  bool butThSt = digitalRead(PIN_BUTTON_THROTTLE); // when pressed 0

  bool currentA = digitalRead(PIN_ENC_A);
  bool down = false;
  bool up = false;
  
  
  // Detect change on A
  if (currentA != lastA) {
    if (digitalRead(PIN_ENC_B) != currentA) {
      up = false;
      down = true;
    } else {
      up = true;
      down = false;
    }
  }
  lastA = currentA;

  if (up && !down) {
    test++;
  }
  if (down && !up) {
    test--;
  }
  
  char message[1000];
  sprintf(message, "RT: %d, LT: %d, SP: %d, encBt: %d, up: %d, down:%d, LSw: %d, RSw: %d, thBT: %d, test: %d\n",
                    thRightVal, thLeftVal, spVal, butEncSt, up,
                    down, swLeftSt, swRightSt, butThSt, test);
  Serial.print(message);
  delay(5);
}
