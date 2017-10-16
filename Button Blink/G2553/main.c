#include <msp430.h> 


/**
 * main.c
 */

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    //LED on P1.0
    P1DIR |= BIT0;
    P1OUT &= ~BIT0;


    //button on P1.3
    P1DIR &= ~BIT3;
    P1REN |= BIT3;
    P1OUT |= BIT3;
    P1IE |= BIT3;
    P1IFG &= ~BIT3;
    P1IES |= BIT3;

    TA0CTL = TASSEL_2 + MC_1 + ID_3 + TACLR; //SMCLK, UP, divided by 1, 1MHz/8
    TA0CCTL0 = CCIE; //enable interrupt
    TA0CCR0 = 0; //Max TimerA reaches before coming down, so 10Hz  signal


    __enable_interrupt();

    while(1){}

    return 0;
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A0(void)
{
    P1OUT ^= BIT0;
}
#pragma vector = PORT1_VECTOR
__interrupt void Port_1(void)
{
    if(TA0CCR0 == 0)
    {
        TA0CCR0 = 12500;
    }else{
        TA0CCR0 = 0;
    }
    P1IES ^= BIT3;
    P1IFG &= ~BIT3;

}
