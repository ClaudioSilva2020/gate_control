/**
 * @file switches.h
 * @author Cláudio Silva (claudiosilva@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef __SWITCHES_H__
#define __SWITCHES_H__

#include <Arduino.h>

#define GPIO0   0
#define GPIO1   1
#define GPIO2   2
#define GPIO3   3


#define GATE_A GPIO0
#define GATE_B GPIO1
#define GATE_OUTPUT OUTPUT

typedef enum switches_state
{
    OFF = LOW,
    ON = HIGH 
}switches_state_t ;


class switches
{
    private:
        int _pin;
    public:
        switches_state_t state;
    
        switches(int pin);
        ~switches();
        void switches_turnon(); //Função que liga o rele
        void switches_turnoff(); //Função que desliga o rele
};

#endif
