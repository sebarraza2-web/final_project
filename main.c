#include "msp.h"
#include "lcdLib.h"
#include "keypad.h"
#include "uart.h"
#include "timers.h"
#include "string.h"
#include "pwm.h"

char buffer[1];
char welcome[] = "PLACE YOUR BETS \r";
char done[] = "NO MORE BETS \r";
char numberBET0[4], key;
char numberBET1[4];
char numberBET2[4];
char numberBET3[4];
char numberBET4[4];
char numberBET5[4];
char numberBET6[4];
char numberBET7[4];
char numberBET8[4];
char numberBET9[4];
char typeBET[7], halfBET[7];
int t, counter, r;
int result, winning;

int adc(){
    return 9; // 1
}

void print_result(int score){
    char win1[] = "ONLY 1, TRY AGAIN \r";
    char win2[] = "ONLY 2, NEXT TIME \r";
    char win3[] = "LUCKY WINNER \r";
    char win0[] = "OUT OF LUCK \r";
    switch(score){
    case 1: transmit_string(win1); break;
    case 2: transmit_string(win2); break;
    case 3: transmit_string(win3); break;
    case 0: transmit_string(win0); break;
    }
}

void picking(){

    key = keypad_get_key();

    switch(key){
    case '1': strcpy(numberBET1, "1\n"); counter++; SysTick_timer(1); transmit_string(numberBET1); break;
    case '2': strcpy(numberBET2, "2\n"); counter++; SysTick_timer(1); transmit_string(numberBET2); break;
    case '3': strcpy(numberBET3, "3\n"); counter++; SysTick_timer(1); transmit_string(numberBET3); break;
    case '4': strcpy(numberBET4, "4\n"); counter++; SysTick_timer(1); transmit_string(numberBET4); break;
    case '5': strcpy(numberBET5, "5\n"); counter++; SysTick_timer(1); transmit_string(numberBET5); break;
    case '6': strcpy(numberBET6, "6\n"); counter++; SysTick_timer(1); transmit_string(numberBET6); break;
    case '7': strcpy(numberBET7, "7\n"); counter++; SysTick_timer(1); transmit_string(numberBET7); break;
    case '8': strcpy(numberBET8, "8\n"); counter++; SysTick_timer(1); transmit_string(numberBET8); break;
    case '9': strcpy(numberBET9, "9\n"); counter++; SysTick_timer(1); transmit_string(numberBET9); break;
    case '0': strcpy(numberBET0, "0\n"); counter++; SysTick_timer(1); transmit_string(numberBET0); break;
    }
    if(key == 'A'){
        while(t < 1){
            strcpy(typeBET, "EVEN\n");
            transmit_string(typeBET);
            t++;
            counter++;
        }
    }
    else if(key == 'B'){
        while(t < 1){
            strcpy(typeBET, "ODD\n");
            transmit_string(typeBET);
            t++;
            counter++;
        }
    }
    else if(key == 'C'){
        while(r < 1){
            strcpy(halfBET, "HIGH\n");
            transmit_string(halfBET);
            r++;
            counter++;
        }
    }
    else if(key == 'D'){
        while(r < 1){
            strcpy(halfBET, "LOW\n");
            transmit_string(halfBET);
            r++;
            counter++;
        }
    }
}

void interrupt_init(){
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
}

void main(void){
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;

    keypad_init();
    uart_init();
    interrupt_init();
    //PWM_Init();
    PCM->CTL1 = PCM_CTL0_KEY_VAL | PCM_CTL1_FORCE_LPM_ENTRY;

    SCB->SCR |= (SCB_SCR_SLEEPDEEP_Msk);

    SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;

    __DSB();

    __sleep();
}
void PORT1_IRQHandler(void)
{
    volatile uint8_t i, j;
    t = 0;
    r = 0;
    counter = 0;
    winning = 0;
    j = 0;
    result = 0;
    strcpy(numberBET0, "   ");
    strcpy(numberBET1, "   ");
    strcpy(numberBET2, "   ");
    strcpy(numberBET3, "   ");
    strcpy(numberBET4, "   ");
    strcpy(numberBET5, "   ");
    strcpy(numberBET6, "   ");
    strcpy(numberBET7, "   ");
    strcpy(numberBET8, "   ");
    strcpy(numberBET9, "   ");
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
        //PWM();
        result = adc();

        if((result  == 1) || (result  == 3) || (result  == 5) || (result  == 7) ||(result  == 9)){
            if(! (strcmp(typeBET, "ODD\n"))){
                winning++;
            }
        }
        if((result  == 2) || (result  == 4) || (result  == 6) || (result  == 8) ||(result  == 0)){
            if(! (strcmp(typeBET, "EVEN\n"))){
                winning++;
            }
        }
        if((result  == 1) || (result  == 2) || (result  == 3) || (result  == 4) ||(result  == 5)){
            if(! (strcmp(halfBET, "HIGH\n"))){
                winning++;
            }
        }
        if((result  == 6) || (result  == 7) || (result  == 8) || (result  == 9) ||(result  == 0)){
            if(! (strcmp(halfBET, "LOW\n"))){
                winning++;
            }
        }
        if(result == 1){
            if(! (strcmp(numberBET1, "1\n"))){
                winning++;
            }
        }
        if(result == 2){
            if(! (strcmp(numberBET2, "2\n"))){
                winning++;
            }
        }
        if(result == 3){
            if(! (strcmp(numberBET3, "3\n"))){
                winning++;
            }
        }
        if(result == 4){
            if(! (strcmp(numberBET4, "4\n"))){
                winning++;
            }
        }
        if(result == 5){
            if(! (strcmp(numberBET5, "5\n"))){
                winning++;
            }
        }
        if(result == 6){
            if(! (strcmp(numberBET6, "6\n"))){
                winning++;
            }
        }
        if(result == 7){
            if(! (strcmp(numberBET7, "7\n"))){
                winning++;
            }
        }
        if(result == 8){
            if(! (strcmp(numberBET8, "8\n"))){
                winning++;
            }
        }
        if(result == 9){
            if(! (strcmp(numberBET9, "9\n"))){
                winning++;
            }
        }
        else{
            if(! (strcmp(numberBET0, "0\n"))){
                winning++;
            }
        }

        print_result(winning);

        P1->IFG &= ~BIT1; // Clear interrupt flag

    }
}
