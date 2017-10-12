#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
    volatile int i;

	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	PM5CTL0 &= ~LOCKLPM5; //Turn off lowpower of FR5994
	//set pin 1 as output
	P1DIR = 0x01;
	//set bit 0 of pin 1 as 0
	P1OUT = 0x00;

	TA0CTL = TASSEL_2 + MC_3 + ID_0; //SMCLK, UPDOWN, divided by 1, 1MHz
    TA0CCTL1 = CCIE; //enable interrupt
    TA0CCR0 = 1000; //Max TimerA reaches before coming down, so 1kHz  signal
    TA0CCR1 = 499;
	
    __enable_interrupt();

    while(1){}

	return 0;
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt void Timer_A(void)
{
    P1OUT ^= BIT0;
}
