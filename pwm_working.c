#include "msp.h"
#include "timers.h"


void PWM_Init(void){
       P6->DIR |= BIT7; // P6.7 set TA2.4
       P6->SEL0 |= BIT7;
       P6->SEL1 &= ~(BIT7);
}


void PWM_forward(void){
        TIMER_A2->CCR[0] = 6900 - 1; // PWM Period
        TIMER_A2->CCTL[4] = TIMER_A_CCTLN_OUTMOD_7; // CCR4 reset/set
        TIMER_A2->CCR[4] = 1000; // CCR4 PWM duty cycle
        TIMER_A2->CTL = TIMER_A_CTL_SSEL__SMCLK | // SMCLK
                TIMER_A_CTL_MC__UP | // Up mode
                TIMER_A_CTL_CLR; // Clear TAR
       // TIMER_A2->CCR[4] = 0;
        SysTick_timer(3);
         TIMER_A2->CCR[4] = 4500;
}

void PWM_reset(void){
        TIMER_A2->CCR[0] = 6900 - 1; // PWM Period
        TIMER_A2->CCTL[4] = TIMER_A_CCTLN_OUTMOD_7; // CCR4 reset/set
        TIMER_A2->CCR[4] = 6500; // CCR4 PWM duty cycle
        TIMER_A2->CTL = TIMER_A_CTL_SSEL__SMCLK | // SMCLK
                TIMER_A_CTL_MC__UP | // Up mode
                TIMER_A_CTL_CLR; // Clear TAR
       // TIMER_A2->CCR[4] = 0;
        SysTick_timer(3);
         TIMER_A2->CCR[4] = 4500;
}


void main(){
    PWM_Init();
    while(1){
    PWM_forward();
    PWM_reset();
    }
}
