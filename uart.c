/*
 * uart.c
 *
 *  Created on: Apr 12, 2022
 *      Author: sebel
 */

#include "msp.h"
#include "uart.h"


void uart_init(void){
    P3->SEL0 |= BIT2 | BIT3; // Selected pins for UCA_2
    EUSCI_A2->CTLW0 |= EUSCI_A_CTLW0_SWRST; // Sets the reset bit to allow configuration
    EUSCI_A2->CTLW0  = 0x00C1;              // Uses SMCLK which runs @ 3MHz
    EUSCI_A2->BRW = (3000000) / (9600); // Baud Rate Calculation used 9600 which is a standard
    EUSCI_A2->MCTLW &= ~0xFFF1;         // No oversampling needed
    EUSCI_A2->CTLW0 &= ~(EUSCI_A_CTLW0_SWRST); // Bit Clears the reset to set new configuration
}

void transmit_string(char *str){   // argument as a string
    while(*str != 0){               // will tranmsit as long as the string has data
        while(!(EUSCI_A2->IFG & EUSCI_A_IFG_TXIFG)); // waits for the TX buffer to be empty
        EUSCI_A2->TXBUF = *str++;                   // sends corresponding character
    }
}


