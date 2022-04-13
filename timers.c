/*
 * timers.c
 *
 *  Created on: Apr 12, 2022
 *      Author: sebel
 */
#include "msp.h"
#include "timers.h"


void SysTick_timer(double x){
    SysTick->CTRL = 5;
    SysTick->VAL = 0;
    SysTick->LOAD = (x*3000000)-1;
    while(!(SysTick->CTRL & 0x00010000));
}



