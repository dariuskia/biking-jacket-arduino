/*
 FEATURES:
 - LEDs are cycled on and off when a button is pressed
 - LEDs are turned off when a button is held
 - Both buttons pressed enables risk mode
 - One button held disables risk mode
*/

// Declaring PIN Variables

// NOTE: Define variables once a physical circuit is acquired

const int leftHand;
const int leftButton;
const int rightHand;
const int rightButton;
const int left;
const int minus;
const int right;
const int RESET;
int leftCounter = RESET;
int rightCounter = RESET;
int riskMode = 0;
int riskModeRecent = 0;

void setup() {
  pinMode(left, OUTPUT);
  pinMode(right, OUTPUT);
  pinMode(leftHand, OUTPUT);
  pinMode(rightHand, OUTPUT);
  pinMode(minus, OUTPUT);
  digitalWrite(minus, LOW);
  pinMode(leftButton, INPUT_PULLUP);
  pinMode(rightButton, INPUT_PULLUP);
}

void loop() {

  if (riskMode == 1) {
    risk();
  }

  if (digitalRead(leftButton) == LOW) {

    while(digitalRead(leftButton) == LOW) {

      if (digitalRead(rightButton) == LOW) {
        riskMode = 1 - riskMode;

        if (riskMode == 0) {
          riskModeRecent = 1;
        }
        return;
      }
    }

    if (leftCounter < RESET) {
      leftCounter = RESET;
      return;
    } else {
      blink(left, leftHand);
    }
  }

  if (digitalRead(rightButton) == LOW) {

    while(digitalRead(rightButton) == LOW) {

      if (digitalRead(leftButton) == LOW) {
        riskMode = 1 - riskMode;
        if (riskMode == 0) {
          riskModeRecent = 1;
        }
        return;
      }
    }

    if (rightCounter < RESET) {
      rightCounter = RESET;
      return;
    } else {
      blink(right, rightHand);
    }
  }

  if (leftCounter != RESET) {
    blink(left, leftHand);
  }

  if (rightCounter != RESET) {
    blink(right, rightHand);
  }
}

void blink(int blinker, int hand) {
  int x;

  if (riskMode == 1 || riskModeRecents == 1) {
    riskModeRecent = 0;
    return;
  }

  if (blinker == left) {
    rightCounter = RESET;

    leftCounter--;

    if (leftCounter <= 0) {
      leftCounter = RESET;
    }
  }

  if (blinker == right) {
    leftCounter = RESET;

    rightCounter--;

    if (rightCounter <= 0) {
      rightCounter = RESET;
    }
  }

  digitalWrite(hand, HIGH);

  for (x = 0; x <= 255; x += 6) {
    analogWrite(blinker, x);
    delay(2);
  }

  digitalWrite(blinker, HIGH);
  delay(95);
  digitalWrite(blinker, LOW);
  delay(80);
  digitalWrite(blinker, HIGH);
  delay(95);
  digitalWrite(blinker, LOW);
  delay(80);
  digitalWrite(blinker, HIGH);
  delay(95);
  digitalWrite(blinker, LOW);
  delay(80);
  digitalWrite(blinker, HIGH);
  delay(95);
  digitalWrite(blinker, LOW);
  delay(80);
  digitalWrite(blinker, HIGH);
  delay(95);

  for (x = 255; x >= 0; x--) {
    analogWrite(blinker, x);
    delay(3);
  }

  digitalWrite(blinker, LOW);

  digitalWrite(hand, LOW);

  delay(240);
}

void risk() {
  riskMode = 1;
  leftCounter = RESET;
  rightCounter = RESET;

  digitalWrite(left, HIGH);
  digitalWrite(right, HIGH);
  digitalWrite(leftHand, HIGH);
  digitalWrite(rightHand, HIGH);

  delay(250);
  if (digitalRead(leftButton) == LOW || digitalRead(rightButton) == LOW) {
    riskMode = 0;
    riskModeRecent = 1;
  }
  delay(250);

  digitalWrite(left, LOW);
  digitalWrite(right, LOW);
  digitalWrite(leftHand, LOW);
  digitalWrite(rightHand, LOW);

  delay(350);
}