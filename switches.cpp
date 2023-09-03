/**
 * @file switches.cpp
 * @author Cláudio Silva (claudiosilva@gmail.com)
 * @version 0.1
 * @date 2023-02-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include "switches.h"

switches::switches(int pin)
{   
    _pin = pin;
    state = LOW;

    pinMode(pin, GATE_OUTPUT);

    digitalWrite(pin, state);
}

switches::~switches()
{
    switches::_pin = 0;
}

void switches::switches_turnon()
{
    digitalWrite(_pin, LOW);
    state = HIGH;
}

void switches::switches_turnoff()
{
    digitalWrite(_pin, HIGH);
    state = LOW;
}

void switches::switches_toogle(float time_delay)
{
    state = !state;
    digitalWrite(_pin, state);
    state = !state;
    delay(time_delay);
    digitalWrite(_pin, state);
}
