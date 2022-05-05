/*
 * pwm.c
 *
 *  Created on: Apr 17, 2022
 *      Author: Sebastian Barraza
 */

#include "msp.h"
#include "timers.h"
#include "pwm.h"

void PWM_Init(void){
       P5->DIR |= BIT7; // P5.7 set TA2.2
       P5->SEL0 |= BIT7;
       P5->SEL1 &= ~(BIT7);
}


void PWM_reset(void){
        TIMER_A2->CCR[0] = 6900 - 1; // PWM Period
        TIMER_A2->CCTL[2] = TIMER_A_CCTLN_OUTMOD_7; // CCR4 reset/set
        TIMER_A2->CCR[2] = 1000; // CCR4 PWM duty cycle
        TIMER_A2->CTL = TIMER_A_CTL_SSEL__SMCLK | // SMCLK
                TIMER_A_CTL_MC__UP | // Up mode
                TIMER_A_CTL_CLR; // Clear TAR
        SysTick_timer(1);
}

void PWM_forward(void){
        TIMER_A2->CCR[0] = 6900 - 1; // PWM Period
        TIMER_A2->CCTL[2] = TIMER_A_CCTLN_OUTMOD_7; // CCR4 reset/set
        TIMER_A2->CCR[2] = 6800; // CCR4 PWM duty cycle
        TIMER_A2->CTL = TIMER_A_CTL_SSEL__SMCLK | // SMCLK
                TIMER_A_CTL_MC__UP | // Up mode
                TIMER_A_CTL_CLR; // Clear TAR
        SysTick_timer(1);
}


