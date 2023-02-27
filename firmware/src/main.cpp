#include <Arduino.h>
#include <EEPROM.h>
#include <Keyboard.h>

struct Button {
  unsigned pin;
  unsigned keys[8];
};

unsigned buttons[4] = {2, 3, 4, 5};
unsigned instruction_buffer[32];
char ctrlKey = KEY_LEFT_CTRL;

void action(int button) {
  switch (button) {
  case 2:
    Keyboard.press(ctrlKey);
    Keyboard.press('n');
    break;
  case 3:
    break;
  case 4:
    break;
  case 5:
    break;
  }
  Keyboard.releaseAll();
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

const int BUFFER_SIZE = 100;
byte buf[BUFFER_SIZE];

void loop() {
  if (Serial.available() > 0) {
    // read the incoming bytes:
    int rlen = Serial.readBytesUntil('\n', buf, BUFFER_SIZE);

    // prints the received data
    Serial.print("I received: ");
    for (int i = 0; i < rlen; i++)
      Serial.print(buf[i]);
  }

  for (int i = 0; i < 4; i++) {
    unsigned isPressed = 1 - digitalRead(buttons[i]);
    if (isPressed > 0) {
      action(buttons[i]);
      Serial.println(buttons[i]);
    }
  }
  delay(50);
}

void read_configuration(int index) {}

void persist_configuration(int index, int keys[8]) {
  unsigned upper_bound = (index + 1) * 8;
  unsigned lower_bound = index * 8;
  unsigned key_index = 0;
  // This may never happen, but I have to make sure upperbound is less than
  // EEPROM length.
  if (upper_bound >= EEPROM.length()) {
    return;
  }
  for (unsigned i = lower_bound; i < upper_bound; i++) {
    unsigned key = keys[key_index];
    if (key) {
      EEPROM.update(i, key);
    } else {
      EEPROM.write(i, 0);
    }
    key_index += 1;
  }
}

void reset_EEPROM() {
  for (unsigned i = 0; i < EEPROM.length(); i++) {
    EEPROM.update(i, 0);
  }
}
