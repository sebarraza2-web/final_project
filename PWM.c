void PWM(void){
        TIMER_A2->CCR[0] = 6900 - 1; // PWM Period
        TIMER_A2->CCTL[4] = TIMER_A_CCTLN_OUTMOD_7; // CCR4 reset/set
        TIMER_A2->CCR[4] = 1000; // CCR4 PWM duty cycle
        TIMER_A2->CTL = TIMER_A_CTL_SSEL__SMCLK | // SMCLK
                TIMER_A_CTL_MC__UP | // Up mode
                TIMER_A_CTL_CLR; // Clear TAR
        SysTick_timer(3.6);
        TIMER_A2->CCR[4] = 0; 
}
