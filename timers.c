/*
 * timers.c
 *
 *  Created on: Apr 12, 2022
 *      Author: sebel
 */
#include "msp.h"
#include "timers.h"


void SysTick_timer(double x){ // Timer used for delays
    SysTick->CTRL = 5; // no interrupts 
    SysTick->VAL = 0; // dummy load value
    SysTick->LOAD = (x*3000000)-1; // takes the argument and does calculation
    while(!(SysTick->CTRL & 0x00010000)); // will stay in this statement until the time is reached
}



