#include <msp430.h> 


/**
 * main.c
 */

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    PM5CTL0 &= ~LOCKLPM5;

    P1DIR |= BIT0;
    P1OUT &= ~BIT0;

    P1DIR &= ~BIT1;
    P1REN |= BIT1;
    P1OUT |= BIT1;
    P1IE |= BIT1;
    P1IFG &= ~BIT1;

    TA0CTL = TASSEL_2 + MC_0 + ID_3 + TACLR; //SMCLK, UP, divided by 1, 1MHz/8
    TA0CCTL0 = CCIE; //enable interrupt
    TA0CCR0 = 12500; //Max TimerA reaches before coming down, so 10Hz  signal


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
    if(TA0CTL == TASSEL_2 + MC_1 + ID_3)
    {
        TA0CTL = TASSEL_2 + MC_0 + ID_3;
    }else{
        TA0CTL = TASSEL_2 + MC_1 + ID_3 + TACLR;
    }
    P1IFG &= ~BIT1;
    P1IES ^= BIT1;
}
