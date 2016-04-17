/*
 * keypad.c
 *
 *  Created on: Mar 2, 2016
 *      Author: breinosa
 */
#include <msp430.h>
#include "keypad.h"
void keypadInit(void){
	/* inputs  */
	P3DIR &= ~(BIT0 | BIT1);        //
	P3REN |= (BIT0 | BIT1);
	P3OUT |= (BIT0 | BIT1);
	P3IES |= (BIT0 | BIT1); // make p1.1 & p1.2 interrupt happen on falling edge
	P3IFG &= ~BIT0;        // clear p1.1 & p1.2 interrupt flag
	P3IFG &= ~BIT1;        // clear p1.1 & p1.2 interrupt flag
	P3IE |= (BIT0 | BIT1);        // enable p1.1 & p1.2 interrupt

	P1DIR &= ~BIT3;
	P1REN |=  BIT3;
	P1OUT |=  BIT3;
	P1IES |=  BIT3; // make p1.1 & p1.2 interrupt happen on falling edge
	P1IFG &= ~BIT3;        // clear p1.1 & p1.2 interrupt flag
	P1IE  |=  BIT3;        // enable p1.1 & p1.2 interrupt

	P2DIR &= ~BIT3;
	P2REN |=  BIT3;
	P2OUT |=  BIT3;
	P2IES |=  BIT3; // make p1.1 & p1.2 interrupt happen on falling edge
	P2IFG &= ~BIT3;        // clear p1.1 & p1.2 interrupt flag
	P2IE  |=  BIT3;        // enable p1.1 & p1.2 interrupt

	/*COLUMN OUTPUTS */
//	P4DIR |= BIT7;
//	P2DIR |= BIT2;
//	P1DIR |= (BIT6|BIT7);
	P4DIR |= BIT7;
	P2DIR |= (BIT2|BIT5);
	P1DIR |= BIT5;


}
void resetPins(void) {
	P4OUT &= ~BIT7;
	P1OUT &= ~BIT5;
	P2OUT &= ~BIT2;
	P2OUT &= ~BIT5;
}
unsigned int scanKeyPad(void) {
	//first column
	P2OUT &= ~BIT2;
	P2OUT |= BIT5;
	P1OUT |= BIT5;
	P4OUT |= BIT7;

	if (!(P2IN & BIT3)) {
		//1
		return 1;
	} else if (!(P3IN & BIT0)) {
		//4
		return 4;
	} else if (!(P1IN & BIT3)) {
		//7
		return 7;
	} else if (!(P3IN & BIT1)) {
		//*
		return 15;
	}
	//second column
	P2OUT |= BIT2;
	P2OUT &= ~BIT5;
	P1OUT |= BIT5;
	P4OUT |= BIT7;

	if (!(P2IN & BIT3)) {
		//2
		return 2;
	} else if (!(P3IN & BIT0)) {
		//5
		return 5;
	} else if (!(P1IN & BIT3)) {
		//8
		return 8;
	} else if (!(P3IN & BIT1)) {
		//0
		return 0;
	}
	//third column
	P2OUT |= BIT2;
	P2OUT |= BIT5;
	P1OUT &= ~BIT5;
	P4OUT |= BIT7;

	if (!(P2IN & BIT3)) {
		//3
		return 3;
	} else if (!(P3IN & BIT0)) {
		//6
		return 6;
	} else if (!(P1IN & BIT3)) {
		//9
		return 9;
	} else if (!(P3IN & BIT1)) {
		//#
		return 14;
	}
	//fourth column
	P2OUT |= BIT2;
	P2OUT |= BIT5;
	P1OUT |= BIT5;
	P4OUT &= ~BIT7;

	if (!(P2IN & BIT3)) {
		//A
		return 10;
	} else if (!(P3IN & BIT0)) {
		//B
		return 11;
	} else if (!(P1IN & BIT3)) {
		//C
		return 12;
	} else if (!(P3IN & BIT1)) {
		//D
		return 13;
	}
	return 23;//random, no choice
}



