void PWM_Init(void){
       P2->DIR |= BIT4; // P2.4 set TA0.1
       P2->SEL0 |= BIT4;
       P2->SEL1 &= ~(BIT4);
}
