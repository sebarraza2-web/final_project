/*
 * uart.c
 *
 *  Created on: Apr 12, 2022
 *      Author: sebel
 */

#include "msp.h"
#include "uart.h"


void uart_init(void){
    P3->SEL0 |= BIT2 | BIT3;
    EUSCI_A2->CTLW0 |= EUSCI_A_CTLW0_SWRST;
    EUSCI_A2->CTLW0  = 0x00C1;
    EUSCI_A2->BRW = 312;
    EUSCI_A2->MCTLW &= ~0xFFF1;
    EUSCI_A2->CTLW0 &= ~(EUSCI_A_CTLW0_SWRST);
}

void transmit_string(char *str){
    while(*str != 0){
        while(!(EUSCI_A2->IFG & EUSCI_A_IFG_TXIFG));
        EUSCI_A2->TXBUF = *str++;
    }
}


