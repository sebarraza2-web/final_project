#include "msp.h"
#include "lcdLib.h"
#include "keypad.h"
#include "uart.h"
#include "timers.h"
#include "string.h"

char buffer[1];
char welcome[] = "PLACE YOUR BETS \r";
char done[] = "NO MORE BETS \r";
char numberBET[1][10], key;
char typeBET[1][10], halfBET[1][10];
int t, counter, r;

void picking(){

    key = keypad_get_key();

    switch(key){
    case '1': strcpy(numberBET[0], "1\n"); counter++; SysTick_timer(1); transmit_string(numberBET); break;
    case '2': strcpy(numberBET[0], "2\n"); counter++; SysTick_timer(1); transmit_string(numberBET); break;
    case '3': strcpy(numberBET[0], "3\n"); counter++; SysTick_timer(1); transmit_string(numberBET); break;
    case '4': strcpy(numberBET[0], "4\n"); counter++; SysTick_timer(1); transmit_string(numberBET); break;
    case '5': strcpy(numberBET[0], "5\n"); counter++; SysTick_timer(1); transmit_string(numberBET); break;
    case '6': strcpy(numberBET[0], "6\n"); counter++; SysTick_timer(1); transmit_string(numberBET); break;
    case '7': strcpy(numberBET[0], "7\n"); counter++; SysTick_timer(1); transmit_string(numberBET); break;
    case '8': strcpy(numberBET[0], "8\n"); counter++; SysTick_timer(1); transmit_string(numberBET); break;
    case '9': strcpy(numberBET[0], "9\n"); counter++; SysTick_timer(1); transmit_string(numberBET); break;
    case '0': strcpy(numberBET[0], "0\n"); counter++; SysTick_timer(1); transmit_string(numberBET); break;
    }
    if(key == 'A'){
        while(t < 1){
            strcpy(typeBET[0], "EVEN\n");
            transmit_string(typeBET);
            t++;
            counter++;
        }
    }
    else if(key == 'B'){
        while(t < 1){
            strcpy(typeBET[0], "ODD\n");
            transmit_string(typeBET);
            t++;
            counter++;
        }
    }
    else if(key == 'C'){
        while(r < 1){
            strcpy(halfBET[0], "HIGH\n");
            transmit_string(halfBET);
            r++;
            counter++;
        }
    }
    else if(key == 'D'){
        while(r < 1){
            strcpy(halfBET[0], "LOW\n");
            transmit_string(halfBET);
            r++;
            counter++;
        }
    }
}

void main(void){
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;
    P1->DIR = ~(uint8_t) BIT1;
    P1->OUT = BIT1;
    P1->REN = BIT1; // Enable pull-up resistor (P1.1 output high)
    P1->SEL0 = 0;
    P1->SEL1 = 0;
    P1->IES = BIT1; // Interrupt on high-to-low transition
    P1->IFG = 0; // Clear all P1 interrupt flags
    P1->IE = BIT1; // Enable interrupt for P1.1
    // Enable Port 1 interrupt on the NVIC
    NVIC->ISER[1] = 1 << ((PORT1_IRQn) & 31);
    __enable_irq();

    keypad_init();
    uart_init();

    while(1){
        t = 0;
        r = 0;
        counter = 0;
        __DSB();
        SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;
        __sleep();
    }
}
void PORT1_IRQHandler(void)
{
    volatile uint8_t i, j;
    // Toggling the output on the LED
    while(j < 1){
        transmit_string(welcome);
        j++;
    }

    if(P1->IFG & BIT1){

        while(counter < 3){
        picking();
        j = 0;
        }
        while(j < 1){
            transmit_string(done);
            j++;
            P1->IFG &= ~BIT1;
        }
        //lcdClear();

    }


    // Delay for switch debounce
    //for(i = 0; i < 10000; i++)
      //  P1->IFG &= ~BIT1; // Clear interrupt flag
}
