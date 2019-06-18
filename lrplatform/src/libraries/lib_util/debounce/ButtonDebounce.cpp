#include "Arduino.h"
#include "ButtonDebounce.h"

ButtonDebounce::ButtonDebounce()
{
    _pin = 0;
    _delay = 0;
    _lastDebounceTime = 0;
    _lastStateBtn = HIGH;
    callback = 0;
}

ButtonDebounce::ButtonDebounce(int pin, unsigned long delay) : ButtonDebounce()
{
  initializeButton(pin, delay);
}

void ButtonDebounce::initializeButton(int pin, unsigned long delay)
{
    pinMode(pin, INPUT_PULLUP);
    _pin = pin;
    _delay = delay;
}

bool ButtonDebounce::isTimeToUpdate()
{
  return (millis() - _lastDebounceTime) > _delay;
}

void ButtonDebounce::update()
{
  if(!isTimeToUpdate())
      return;

  _lastDebounceTime = millis();

  int btnState = digitalRead(_pin);

  if(btnState == _lastStateBtn)
      return;

  _lastStateBtn = btnState;

  if(this->callback != 0)
      this->callback(_lastStateBtn);
}

int ButtonDebounce::state()
{
  return _lastStateBtn;
}

void ButtonDebounce::setCallback(BTN_CALLBACK)
{
  this->callback = callback;
}
