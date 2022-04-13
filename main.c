#include "msp.h"
#include <lcdLib.h>
#include "keypad.h"

char buffer[1];

void uart_init(void){
    P3->SEL0 |= BIT2 | BIT3;
    EUSCI_A2->CTLW0 |= EUSCI_A_CTLW0_SWRST;
    EUSCI_A2->CTLW0  = 0x00C1;
    EUSCI_A2->BRW = 312;
    EUSCI_A2->MCTLW &= ~0xFFF1;
    EUSCI_A2->CTLW0 &= ~(EUSCI_A_CTLW0_SWRST);
}
void SysTick_timer(double x){
    SysTick->CTRL = 5;
    SysTick->VAL = 0;
    SysTick->LOAD = (x*3000000)-1;
    while(!(SysTick->CTRL & 0x00010000));
}
void transmit(void){
    //int i;
    //for(i = 0; i <= sizeof(buffer); i++){
        SysTick_timer(1);
        if(EUSCI_A2->IFG & EUSCI_A_IFG_TXIFG){
            EUSCI_A2->TXBUF = buffer[0];
        }
   // }
}

void main(void){
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;
    //uart_init();
    keypad_init();
    lcdInit();
    lcdClear();
    char key;
    while(1){
        key = keypad_get_key();

        switch(key){
        case '1': buffer[0] = '1'; break;
        case '2': buffer[0] = '2'; break;
        case '3': buffer[0] = '3'; break;
        case '4': buffer[0] = '4'; break;
        case '5': buffer[0] = '5'; break;
        case '6': buffer[0] = '6'; break;
        case '7': buffer[0] = '7'; break;
        case '8': buffer[0] = '8'; break;
        case '9': buffer[0] = '9'; break;
        case '0': buffer[0] = '0'; break;
        case 'A': buffer[0] = 'A'; break;
        case 'B': buffer[0] = 'B'; break;
        case 'C': buffer[0] = 'C'; break;
        case 'D': buffer[0] = 'D'; break;
        }
        lcdSetText("Hello", 0, 0);
        lcdSetText(buffer, 0, 1);
        SysTick_timer(1);



    }

}
