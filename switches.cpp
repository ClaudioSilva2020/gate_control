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
    state = OFF;

    pinMode(pin, GATE_OUTPUT);

    digitalWrite(pin, state);
}

switches::~switches()
{
    switches::_pin = 0;
}

void switches::switches_turnon()
{
    digitalWrite(_pin, OFF);
    state = ON;
}

void switches::switches_turnoff()
{
    digitalWrite(_pin, ON);
    state = OFF;
}
