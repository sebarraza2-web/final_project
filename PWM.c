void PWM(void){
        TIMER_A0->CCR[0] = 6900 - 1;                // PWM Period
        TIMER_A0->CCTL[1] = TIMER_A_CCTLN_OUTMOD_7; // CCR1 reset/set
        TIMER_A0->CCR[1] = 1000; // CCR1 PWM duty cycle
        TIMER_A0->CTL = TIMER_A_CTL_SSEL__SMCLK |  // SMCLK
                TIMER_A_CTL_MC__UP | 
                TIMER_A_CTL_CLR; 
        SysTick_timer(3.596);                      // Delay for motor run time
        TIMER_A0->CCR[1] = 0;                     // CCR1 PWM duty cycle
}
