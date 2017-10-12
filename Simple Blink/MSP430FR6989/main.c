#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
    volatile int i;

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    PM5CTL0 &= ~LOCKLPM5; //Turn off lowpower of FR5994
    //set pin 1 as output
    P1DIR |= BIT0;
    //set bit 0 of pin 1 as 0
    P1OUT &= ~BIT0;

    TA0CTL = TASSEL_2 + MC_1 + ID_3; //SMCLK, UP, divided by 1, 1MHz/8
    TA0CCTL0 = CCIE; //enable interrupt
    TA0CCR0 = 12500; //Max TimerA reaches before coming down, so 10Hz  signal

    __enable_interrupt();

    while(1){}

    return 0;
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
    P1OUT ^= BIT0;
}
