void PWM_Init(void){
       P6->DIR |= BIT7; // P6.7 set TA2.4
       P6->SEL0 |= BIT7;
       P6->SEL1 &= ~(BIT7);
}
