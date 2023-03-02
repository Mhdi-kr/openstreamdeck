#include <Arduino.h>
#include <Keyboard.h>

// device button indexes
unsigned buttons[4] = {2, 3, 4, 5};

char ctrlKey = KEY_LEFT_CTRL;
char shiftKey = KEY_LEFT_SHIFT;

char numOne = KEY_KP_1;
char numTwo = KEY_KP_2;
char numThree = KEY_KP_3;
char numFour = KEY_KP_4;

void action(int button) {
  switch (button) {
  case 2:
    Keyboard.press(ctrlKey);
    Keyboard.press(shiftKey);
    Keyboard.press(numOne);
    break;
  case 3:
    Keyboard.press(ctrlKey);
    Keyboard.press(shiftKey);
    Keyboard.press(numTwo);
    break;
  case 4:
    Keyboard.press(ctrlKey);
    Keyboard.press(shiftKey);
    Keyboard.press(numThree);
    break;
  case 5:
    Keyboard.press(ctrlKey);
    Keyboard.press(shiftKey);
    Keyboard.press(numFour);
    break;
  }
  Keyboard.releaseAll();
  delay(100);
}

void setup() {
  // start serial connection
  Serial.begin(115200);
  Keyboard.begin();

  // configure pin 2 as an input and enable the internal pull-up resistor
  for (int i = 0; i < 4; i++) {
    pinMode(buttons[i], INPUT_PULLUP);
  }
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  for (int i = 0; i < 4; i++) {
    unsigned isPressed = 1 - digitalRead(buttons[i]);
    if (isPressed > 0) {
      action(buttons[i]);
    }
  }
  delay(50);
}
