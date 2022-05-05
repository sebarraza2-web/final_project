/* Final Project for EE 3376
 * 
 * Authors: Sebastian Barraza & Vicente Gomez
 * 
 * Description: The following code is intended to automate an Electric Roulette.
 *              The user wakes the system up by pressing P1.1 and going into the game mode
 *              which will display certain instructions on a TV via UART. Once the game comes to an 
 *              end the system will go back to sleep.
 */


#include "msp.h" //libraries that will be used for this project
#include "lcdLib.h"
#include "keypad.h"
#include "uart.h"
#include "timers.h"
#include "string.h"
#include "ADC.h"
#include "pwm.h"
#include "stdio.h"

char buffer[1];                             
char welcome[] = "PLACE YOUR BETS \r"; // Strings that will be displayed on the screen via UART
char spin[] = "WHEEL WILL SPIN \r";
char done_spin[] = "DONE SPINNING \r";
char done[] = "NO MORE BETS \r";

char numberBET0[4], key; // Preallocated data for the user inputs for the different bets
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
int t, counter, r, k, y, f; // data types that are used as counters throughout the code
int result, winning;


void print_result(int score){               // this method will be used to display how the game went
    char win1[] = "ONLY 1, TRY AGAIN \r";   // takes as an argument the tallied up score of the bets placed correctly
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

void picking(){ // this method is called to recieve what the user inputted

    key = keypad_get_key(); // the function returns the value pressed from the keypad and stores it into key

    switch(key){
    case '1': strcpy(numberBET1, "1\n"); counter++; SysTick_timer(1); transmit_string(numberBET1); break; // counter is set up to only allow 3 bets
    case '2': strcpy(numberBET2, "2\n"); counter++; SysTick_timer(1); transmit_string(numberBET2); break; // delay is used for debouncing switches
    case '3': strcpy(numberBET3, "3\n"); counter++; SysTick_timer(1); transmit_string(numberBET3); break; // transmit function sends data to screen
    case '4': strcpy(numberBET4, "4\n"); counter++; SysTick_timer(1); transmit_string(numberBET4); break;
    case '5': strcpy(numberBET5, "5\n"); counter++; SysTick_timer(1); transmit_string(numberBET5); break;
    case '6': strcpy(numberBET6, "6\n"); counter++; SysTick_timer(1); transmit_string(numberBET6); break;
    case '7': strcpy(numberBET7, "7\n"); counter++; SysTick_timer(1); transmit_string(numberBET7); break;
    case '8': strcpy(numberBET8, "8\n"); counter++; SysTick_timer(1); transmit_string(numberBET8); break;
    case '9': strcpy(numberBET9, "9\n"); counter++; SysTick_timer(1); transmit_string(numberBET9); break;
    case '0': strcpy(numberBET0, "0\n"); counter++; SysTick_timer(1); transmit_string(numberBET0); break;
    }
    if(key == 'A'){                         // The following cases will store selected bet
        while(t < 1){                       // store into typeBET and send it to screen via UART
            strcpy(typeBET, "EVEN\n");      // counter of t is needed to display only once
            transmit_string(typeBET);       // the latter is intended for the following cases too
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

void interrupt_init(){             // set up interrupt driven switch
    P1->OUT = BIT1;
    P1->REN = BIT1; // Enable pull-up resistor (P1.1 output high)
    P1->IES = BIT1; // Interrupt on high-to-low transition
    P1->IFG = 0; // Clear all P1 interrupt flags
    P1->IE = BIT1; // Enable interrupt for P1.1
    // Enable Port 1 interrupt on the NVIC
    NVIC->ISER[1] = 1 << ((PORT1_IRQn) & 31);
    __enable_irq();
}

void main(void){   // main function where the system is sent to sleep
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD; // Initialize WTD Timer

    keypad_init();                              // Initialization of peripherals needed 
    uart_init();
    interrupt_init();
    PWM_Init();
    ADC_init();
    __enable_irq();                                                 //used to enable interrupts

    SCB -> SCR &= ~SCB_SCR_SLEEPONEXIT_Msk;                         //allows LPM to occur once it exits interrupts
    __DSB();

    while(1)
    {
        ADC14 -> CTL0 |= 0x03;                                      //enables conversion and starts sampling ADC
        __sleep();                                                  //sleep
    }
}
    void PORT1_IRQHandler(void)
    {
        volatile uint8_t i, j;
        t = 0; // used to clear any counters or allocated data before the game starts 
        r = 0; // intended only if the system will be used again
        k = 0; // ^^ for lines 139-157
        f = 0;
        y = 0;
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

        while(j < 1){ // transmit only welcome string only once
            transmit_string(welcome);
            j++;
        }

        if(P1->IFG & BIT1){ 

            while(counter < 3){ // goes into picking method 3 times allowing only 3 BETS
                picking();
                j = 0;
            }
            while(j < 1){  // transmit only done string only once
                transmit_string(done);
                j++;
                SysTick_timer(5); // timer for 5 seconds to make the game enjoyable
            }
            while(k < 1){
                transmit_string(spin); // will notify the user that the wheel is about to spin only once
                SysTick_timer(5);
                k++;
            }
            SysTick_timer(2);
            while(f < 3){
                PWM_forward(); // used to make the motor spin 180
                PWM_reset();   // used to make the motor spin -180
                f++;
            }
            SysTick_timer(2);
            while(y < 1){
                transmit_string(done_spin);   // displays the motor state and that the system is ready to read
                SysTick_timer(1);              // where the ball landed
                y++;
            }
            result = ADC_get_value();           // the function returns the value of where the ball landed
            
            // The following conditions are for the types of cases that can occur and compares it
            // to what the user selected
            
            if((result  == 1) || (result  == 3) || (result  == 5) || (result  == 7) ||(result  == 9)){ // if the returned value is odd
                if(! (strcmp(typeBET, "ODD\n"))){ // program compares it to what the user selected 
                    winning++;                     // tallies up the score
                }
            }
            if((result  == 2) || (result  == 4) || (result  == 6) || (result  == 8) ||(result  == 0)){ // the same is for the latter
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

            print_result(winning); // sends the accumulated score to print result

            P1->IFG &= ~BIT1; // Clear interrupt flag

        }
    }
