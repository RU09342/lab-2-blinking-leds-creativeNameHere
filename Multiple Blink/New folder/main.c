#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	PM5CTL0 &= ~LOCKLPM5;

	P1DIR |= BIT0;
	P9DIR |= BIT7;

	P1OUT &= ~BIT0;
	P9OUT &= ~BIT7;

	TA0CTL = TASSEL_2 + MC_1 + ID_3; //SMCLK, UP, divided by 1, 1MHz/8
    TA0CCTL0 = CCIE; //enable interrupt
    TA0CCR0 = 12500; //Max TimerA reaches before coming down, so 10Hz  signal

    TA1CTL = TASSEL_2 + MC_1 + ID_3;
    TA1CCTL0 = CCIE;
    TA1CCR0 = 25000;

    __enable_interrupt();

    while(1){}

	return 0;
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A0(void)
{
    P1OUT ^= BIT0;
}
#pragma vector = TIMER1_A0_VECTOR
__interrupt void Timer_A1(void)
{
    P9OUT ^= BIT7;
}

