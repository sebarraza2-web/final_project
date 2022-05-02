#include "msp.h"
#include "timers.h"
#include "stdio.h"
int result;

/*
int voltage(int num){
    float result =  (3.3 * num) / (16383);
    if(result < 2.500000) return 0;
    return 3;
}*/
double voltage(int num){
    return  (3.3 * num) / (16383);
}

void ADC_init()
{

    P5->SEL1 |= BIT5 | BIT4 | BIT2 | BIT1 | BIT0;
     P5->SEL0 |= BIT5| BIT4 | BIT2 | BIT1 | BIT0;

     P4->SEL1 |= BIT7 | BIT5 | BIT4 | BIT3  | BIT2;
     P4->SEL0 |= BIT7 | BIT5| BIT4 | BIT3  | BIT2;


     ADC14->CTL0 = ADC14_CTL0_ON |
             ADC14_CTL0_MSC |
             ADC14_CTL0_SHP |
             ADC14_CTL0_CONSEQ_3;

     ADC14->MCTL[0] = ADC14_MCTLN_INCH_0; // ref+=AVcc, channel = A0
     ADC14->MCTL[1] = ADC14_MCTLN_INCH_1; // ref+=AVcc, channel = A1
     ADC14->MCTL[2] = ADC14_MCTLN_INCH_3; // ref+=AVcc, channel = A3, end seq.
     ADC14->MCTL[3] = ADC14_MCTLN_INCH_4;
     ADC14->MCTL[4] = ADC14_MCTLN_INCH_5;
     ADC14->MCTL[5] = ADC14_MCTLN_INCH_6;
     ADC14->MCTL[6] = ADC14_MCTLN_INCH_8;
     ADC14->MCTL[7] = ADC14_MCTLN_INCH_9;
     ADC14->MCTL[8] = ADC14_MCTLN_INCH_10;
     ADC14->MCTL[9] = ADC14_MCTLN_INCH_11|
             ADC14_MCTLN_EOS;
}

int main(){
    ADC_init();
    ADC14 -> CTL0 |= 0x03;
    double A0results;
    double A1results;
    double A2results;
    double A3results;
    double A4results;
    double A5results;
    double A6results;
    double A7results;
    double A8results;
    double A9results;

    while(1)
    {
        //SysTick_timer(1);

        A0results =  voltage(ADC14->MEM[0]); //P5.5 works A0
        A1results =  voltage(ADC14->MEM[1]); //P5.4 works A1
        A2results =  voltage(ADC14->MEM[2]); // P5.2 works A3
        A3results =  voltage(ADC14->MEM[3]); // P5.1 works A4
        A4results =  voltage(ADC14->MEM[4]); // P5.0 works A5
        A5results =  voltage(ADC14->MEM[5]); // P4.7 works A6
        A6results =  voltage(ADC14->MEM[6]); // P4.5 works A8
        A7results =  voltage(ADC14->MEM[7]); // P4.4 works A9
        A8results =  voltage(ADC14->MEM[8]); // P4.3 works A10
        A9results =  voltage(ADC14->MEM[9]); // P4.2 works A11

        //printf("0 = %f\t", A0results);
        //printf("1 = %f\t", A1results);
        //printf("2 = %f\n", A2results);
        //printf("3 = %f\t", A3results);
        //printf("4 = %f\t", A4results);
        //printf("5 = %f\t", A5results);
        //printf("6 = %f\t", A6results);
        //printf("7 = %f\t", A7results);
        //printf("8 = %f\t", A8results);
        //printf("9 = %f\n", A9results);




        if(A0results < 2.9){
            result = 0;
        }
        if(A1results < 2){
            result = 1;
        }
        if(A2results < 3){
            result = 2;
        }
        if(A3results < 2){
            result = 3;
        }
        if(A4results < 2){
            result = 4;
        }
        if(A5results < 3){
            result = 5;
        }
        if(A6results < 3.2){
            result = 6;
        }
        if(A7results < 3.1){
            result = 7;
        }
        if(A8results < 2.7){
            result = 8;
        }
        if(A9results < 3){
            result = 9;
        }
        printf(" %i\n", result);
    }
}



