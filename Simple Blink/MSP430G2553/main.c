#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    //set pin 1 as output
    P1DIR |= BIT0;
    //set bit 0 of pin 1 as 0
    P1OUT &= ~BIT0;


    TA0CTL |= TASSEL_2 + MC_1 + ID_3 + TACLR; //ACLK, UP, divided by 8
    TA0CCTL0 |= CCIE; //enable interrupt
    TA0CCR0 = 12500; //Max TimerA reaches before coming down

    __enable_interrupt();

    while(1);

    return 0;
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A0(void)
{
    P1OUT ^=BIT0;
}
