#include "msp.h"

float A0results;
float A1results;
float A2results;
float A3results;
float A4results;
float A5results;
float A6results;
float A7results;
float A8results;
float A9results;

float voltage(int num){
    return  (3.3 * num) / (16383);
}

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

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
    ADC14->MCTL[3] = ADC14_MCTLN_INCH_3; // ref+=AVcc, channel = A3, end seq.
    ADC14->MCTL[4] = ADC14_MCTLN_INCH_4;
    ADC14->MCTL[5] = ADC14_MCTLN_INCH_5;
    ADC14->MCTL[6] = ADC14_MCTLN_INCH_6;
    ADC14->MCTL[8] = ADC14_MCTLN_INCH_8;
    ADC14->MCTL[9] = ADC14_MCTLN_INCH_9;
    ADC14->MCTL[10] = ADC14_MCTLN_INCH_10;
    ADC14->MCTL[11] = ADC14_MCTLN_INCH_11|
            ADC14_MCTLN_EOS;

    while(1){
        ADC14->CTL0 |= ADC14_CTL0_ENC |
                ADC14_CTL0_SC;

        A0results =  voltage(ADC14->MEM[0]); //P5.5 works A0
        A1results =  voltage(ADC14->MEM[1]); //P5.4 works A1
        A2results =  voltage(ADC14->MEM[3]); // P5.2 works A3
        A3results =  voltage(ADC14->MEM[4]); // P5.1 works A4
        A4results =  voltage(ADC14->MEM[5]); // P5.0 works A5
        A5results =  voltage(ADC14->MEM[6]); // P4.7 works A6
        A6results =  voltage(ADC14->MEM[8]); // P4.5 works A8
        A7results =  voltage(ADC14->MEM[9]); // P4.4 works A9
        A8results =  voltage(ADC14->MEM[10]); // P4.3 works A10
        A9results =  voltage(ADC14->MEM[11]); // P4.2 works A11

        if(A0results < 2){
            return 0;
        }
        if(A1results < 2){
            return 1;
        }
        if(A2results < 2){
            return 2;
        }
        if(A3results < 3){
            return 3;
        }
        if(A4results < 2){
            return 4;
        }
        if(A5results < 0.5){
            return 5;
        }
        if(A6results < 2){
            return 6;
        }
        if(A7results < 2){
            return 7;
        }
        if(A8results < 2){
            return 8;
        }
        if(A9results < 2){
            return 9;
        }
        return 11;

    }
}
