/*
  NEStroller
  A simple NES controller interface for the Arduino
  Jared De Blander
  https://github.com/jared0x90
*/

#include "Arduino.h"
#include "NEStroller.h"

#define TIMING_DELAY    12

// -----------------------------------------------------------------------------
// NEStroller
// -----------------------------------------------------------------------------
NEStroller::NEStroller() {

}

void NEStroller::begin(int pinClock, int pinLatch, int pinDataIn) {
  _pin_clock = pinClock;
  _pin_latch = pinLatch;
  _pin_data_in = pinDataIn;

  pinMode(_pin_clock , OUTPUT);
  pinMode(_pin_latch , OUTPUT);
  pinMode(_pin_data_in , INPUT);
}

void NEStroller::updateButtons() {
  // reset button states
  _button_states = 0;

  // Pulse the latch (aka strobe pin)
  digitalWrite(_pin_latch, HIGH);
  delayMicroseconds(TIMING_DELAY);
  digitalWrite(_pin_latch, LOW);

  for (int buttons = 7; buttons >= 0; buttons--) {
    _button_states |= digitalRead(_pin_data_in) << buttons;
    delayMicroseconds(TIMING_DELAY);
    digitalWrite(_pin_clock, HIGH);
    delayMicroseconds(TIMING_DELAY);
    digitalWrite(_pin_clock, LOW);
  }
}

bool NEStroller::getButtonPressed(int button_requested) {
  return bitRead(_button_states, button_requested) == 0;
}

byte NEStroller::getButtons() {
  return _button_states;
}

// -----------------------------------------------------------------------------
// SNEStroller
// -----------------------------------------------------------------------------

SNEStroller::SNEStroller() {

}

void SNEStroller::begin(int pinClock, int pinLatch, int pinDataIn) {
  _pin_clock = pinClock;
  _pin_latch = pinLatch;
  _pin_data_in = pinDataIn;

  pinMode(_pin_clock , OUTPUT);
  pinMode(_pin_latch , OUTPUT);
  pinMode(_pin_data_in , INPUT);
}

void SNEStroller::updateButtons() {
  // reset button states
  _button_states = 0;

  // Pulse the latch (aka strobe pin)
  digitalWrite(_pin_latch, HIGH);
  delayMicroseconds(TIMING_DELAY *10);
  digitalWrite(_pin_latch, LOW);

  // Serial.print("[begin]");
  for (int buttons = 15; buttons >= 0; buttons--) {
    auto data_in = digitalRead(_pin_data_in);
    // Serial.print(data_in);
    // Serial.print("  ");
    _button_states |= digitalRead(_pin_data_in) << buttons;
    delayMicroseconds(TIMING_DELAY);
    digitalWrite(_pin_clock, HIGH);
    delayMicroseconds(TIMING_DELAY);
    digitalWrite(_pin_clock, LOW);
  }
  // Serial.println("[end]");
}

bool SNEStroller::getButtonPressed(int button_requested) {
  return bitRead(_button_states, button_requested) == 0;
}

uint16_t SNEStroller::getButtons() {
  return _button_states;
}
