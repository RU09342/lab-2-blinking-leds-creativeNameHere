#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{

    volatile int i;

	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	PM5CTL0 &= ~LOCKLPM5; //Turn off lowpower of FR5994

	P1DIR = 0x02;
	P5DIR = 0x00;
	P5REN = 0x20;
	P5OUT = 0x20;

	for(;;){

	    volatile int n = P5IN & 0x20;

	    if(n == 0x00){
	        P1OUT ^= 0x02;
            for (i=0x6000; i> 0; i--);
        }else{
            P1OUT &= 0x00;
        }
	}
	
	return 0;
}
