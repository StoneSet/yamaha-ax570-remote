#include <IRremote.h> //only work with pin 3 of the arduino
#include "LowPower.h"//only work with atmega 328/atmega128, not with attiny/atmega8 for example

// IR CODE CAN BE FOUND HERE : http://lirc-remotes.sourceforge.net/remotes-table.html

IRsend irsend;

const int b1  = 4;  //TUNER
const int b2  = 8;  //CD
const int b3  = 6;  //PHONO
const int b4  = 5;  //AUX
const int b5  = 7;  //POWER
const int b6  = 2;  //VOL+
const int b7  = 9;  //VOL-

int timer;
int modeCounter = 0;

void wakeUp() {
  timer = 0;
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(b1, INPUT_PULLUP); // use the internal resistance because why not
  pinMode(b2, INPUT_PULLUP);
  pinMode(b3, INPUT_PULLUP);
  pinMode(b4, INPUT_PULLUP);
  pinMode(b5, INPUT_PULLUP);
  pinMode(b6, INPUT_PULLUP);
  pinMode(b7, INPUT_PULLUP);
}

void loop() {
  int value = digitalRead(b1);
  attachInterrupt(0, wakeUp, HIGH);
  while (timer < 10000) {
    if (digitalRead(b1) == LOW) {
      timer = 0;
      irsend.sendNEC(0x5EA16897, 32); //ir code is on 32 bits
      delay(500);
      Serial.println(value); //to check if the button is high or low
    }

    if (digitalRead(b2) == LOW) {
      timer = 0;
      irsend.sendNEC(0x5EA1A857, 32);
      delay(500);
    }

    if (digitalRead(b3) == LOW) {
      timer = 0;
      irsend.sendNEC(0x5EA128D7, 32);
      delay(500);
    }

    if (digitalRead(b4) == LOW) {
      timer = 0;
      irsend.sendNEC(0x5EA1E817, 32);
      delay(500);
    }

    if (digitalRead(b5) == LOW) {
      timer = 0;
      irsend.sendNEC(0x5EA1F807, 32);
      delay(500); //500ms to prevent a loop btw on and off
    }

    if (digitalRead(b6) == LOW) { //   /!\ the remote will be in sleep mode after a few seconds, you are going to have to push THIS particular button to wake up the remote
      timer = 0;
      irsend.sendNEC(0x5EA158A7, 32);
      delay(20);
    }

    if (digitalRead(b7) == LOW) {
      timer = 0;
      irsend.sendNEC(0x5EA1D827, 32);
      delay(20);
    }
    delay(1);
    timer = timer + 1;

  }
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
}

//StoneSet - 2020
