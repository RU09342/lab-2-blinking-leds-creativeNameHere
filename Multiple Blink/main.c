#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
    volatile int i;

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    PM5CTL0 &= ~LOCKLPM5; //Turn off lowpower of FR5994
    //set pin 1.1 and 1.0 and as output
    P1DIR = 0x03;
    //set bit 0 and bit 1 of pin 1 as 0
    P1OUT = 0x00;

    for(;;){

        //xor bit 0, toggling it
        P1OUT ^= 0x03;
        //delay for 3000 cycles
        for (i=0x3000; i> 0; i--);
        //xor bit 1, toggling it
        P1OUT ^= 0x02;
        //delay for 3000 cycles
        for (i=0x3000; i> 0; i--);
    }

    return 0;
}
