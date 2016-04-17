/*
 * main.c
 */

#include "lcd.h"
#include "graphics.h"

#include "ports.h"
#include "keypad.h"
#include "Lab7.h"
#include <stdio.h>

/*************** prototypes ********************************************/
volatile unsigned int startup = 0;
void setSamplingFrequency(void);
void selectModeChannel(void);

/************************ interrupts ***********************************/
// PIN INTERRUPTS:
#pragma vector = PORT1_VECTOR
__interrupt void p1_ISR() {
	switch (P1IV) {
	case P1IV_NONE:
		break;
	case P1IV_P1IFG0:
		break;
	case P1IV_P1IFG1:
		if (startup) {
			interuptPin = 5;
			P1IE &= ~BIT1;			// Disable interrupt while debouncing
			P1IES ^= BIT1;			// Wait for opposite action (other edge)
			TA2CCTL0 = CCIE;		// Enable debounce timer interrupt
			TA2CTL = TIMER_CFG_UP;	// Start debounce timer
		}
		break;
	case P1IV_P1IFG2:
		if (startup) {
			interuptPin = 6;
			P1IE &= ~BIT2;			// Disable interrupt while debouncing
			P1IES ^= BIT2;			// Wait for opposite action (other edge)
			TA2CCTL0 = CCIE;		// Enable debounce timer interrupt
			TA2CTL = TIMER_CFG_UP;	// Start debounce timer
		}
		break;
	case P1IV_P1IFG3:
		if (startup) {
			interuptPin = 1;
			P1IE &= ~BIT3;			// Disable interrupt while debouncing
			P1IES ^= BIT3;			// Wait for opposite action (other edge)
			TA2CCTL0 = CCIE;		// Enable debounce timer interrupt
			TA2CTL = TIMER_CFG_UP;	// Start debounce timer
			key = scanKeyPad();
			resetPins();
		}
		break;
	case P1IV_P1IFG4:
		break;
	case P1IV_P1IFG5:
		break;
	case P1IV_P1IFG6:
		break;
	case P1IV_P1IFG7:
		break;
	default:
		break;
	}
}

#pragma vector = PORT2_VECTOR
__interrupt void p2_ISR() {
	switch (P2IV) {
	case P2IV_NONE:
		break;
	case P2IV_P2IFG0:
		////////////////////
		///CHANNEL 1////////
		////////////////////
		TA3CCTL1 = CCIE;   // enable timer interrupt to sample pin
		TA3CTL = TASSEL__SMCLK | MC__CONTINUOUS | TACLR;
		channel1[channelCounter] = ((P2IN & BIT0) ? 1 : 0); //p2.0
		channel2[channelCounter] = ((P2IN & BIT1) ? 1 : 0); //p2.1
		channel3[channelCounter] = ((P2IN & BIT6) ? 1 : 0); //p2.6
		channel4[channelCounter] = ((P2IN & BIT7) ? 1 : 0); //p2.7
		channelCounter++;
		P2IE &= ~BIT0; //disable pin interrupt

		break;
	case P2IV_P2IFG1:
		////////////////////
		///CHANNEL 2////////
		////////////////////
		TA3CCTL1 = CCIE;
		TA3CTL = TASSEL__SMCLK | MC__CONTINUOUS | TACLR;
		channel1[channelCounter] = ((P2IN & BIT0) ? 1 : 0); //p2.0
		channel2[channelCounter] = ((P2IN & BIT1) ? 1 : 0); //p2.1
		channel3[channelCounter] = ((P2IN & BIT6) ? 1 : 0); //p2.6
		channel4[channelCounter] = ((P2IN & BIT7) ? 1 : 0); //p2.7
		channelCounter++;
		P2IE &= ~BIT1; //disable pin interrupt
		break;
	case P2IV_P2IFG2:
		break;
	case P2IV_P2IFG3:
		if (startup) {
			interuptPin = 2;
			P2IE &= ~BIT3;			// Disable interrupt while debouncing
			P2IES ^= BIT3;			// Wait for opposite action (other edge)
			TA2CCTL0 = CCIE;		// Enable debounce timer interrupt
			TA2CTL = TIMER_CFG_UP;	// Start debounce timer
			key = scanKeyPad();
			resetPins();
		}
		break;
	case P2IV_P2IFG4:
		break;
	case P2IV_P2IFG5:
		break;
	case P2IV_P2IFG6:
		////////////////////
		///CHANNEL 3////////
		////////////////////
		TA3CCTL1 = CCIE;
		TA3CTL = TASSEL__SMCLK | MC__CONTINUOUS | TACLR;
		channel1[channelCounter] = ((P2IN & BIT0) ? 1 : 0); //p2.0
		channel2[channelCounter] = ((P2IN & BIT1) ? 1 : 0); //p2.1
		channel3[channelCounter] = ((P2IN & BIT6) ? 1 : 0); //p2.6
		channel4[channelCounter] = ((P2IN & BIT7) ? 1 : 0); //p2.7
		channelCounter++;
		P2IE &= ~BIT6; // disable pin interrupt
		break;
	case P2IV_P2IFG7:
		////////////////////
		///CHANNEL 4////////
		////////////////////
		TA3CCTL1 = CCIE;
		TA3CTL = TASSEL__SMCLK | MC__CONTINUOUS | TACLR;
		channel1[channelCounter] = ((P2IN & BIT0) ? 1 : 0); //p2.0
		channel2[channelCounter] = ((P2IN & BIT1) ? 1 : 0); //p2.1
		channel3[channelCounter] = ((P2IN & BIT6) ? 1 : 0); //p2.6
		channel4[channelCounter] = ((P2IN & BIT7) ? 1 : 0); //p2.7
		channelCounter++;
		P2IE &= ~BIT7; // disable pin interrupt
		break;
	default:
		break;
	}
}
#pragma vector = PORT3_VECTOR
__interrupt void p3_ISR() {
	switch (P3IV) {
	case P3IV_NONE:
		break;
	case P3IV_P3IFG0:
		if (startup) {
			interuptPin = 3;
			P3IE &= ~BIT0;			// Disable interrupt while debouncing
			P3IES ^= BIT0;			// Wait for opposite action (other edge)
			TA2CCTL0 = CCIE;		// Enable debounce timer interrupt
			TA2CTL = TIMER_CFG_UP
			;	// Start debounce timer
			key = scanKeyPad();
			resetPins();
		}
		break;
	case P3IV_P3IFG1:
		if (startup) {
			interuptPin = 4;
			P3IE &= ~BIT1;			// Disable interrupt while debouncing
			P3IES ^= BIT1;			// Wait for opposite action (other edge)
			TA2CCTL0 = CCIE;		// Enable debounce timer interrupt
			TA2CTL = TIMER_CFG_UP
			;	// Start debounce timer
			key = scanKeyPad();
			resetPins();
		}
		break;
	case P3IV_P3IFG2:
		break;
	case P3IV_P3IFG3:
		break;
	case P3IV_P3IFG4:
		break;
	case P3IV_P3IFG5:
		break;
	case P3IV_P3IFG6:
		break;
	case P3IV_P3IFG7:
		break;
	default:
		break;
	}
}

// TIMER INTERUPTS:
/********************* TIMER INTERUPT DEFINITION *******************************************/
#pragma vector = TIMER2_A0_VECTOR
__interrupt void debounce_ISR() {
	TA2CCTL0 = 0;				  // Disable debounce timer interrupt
	TA2CTL = TIMER_CFG_STOP
	;	  // Stop debounce timer
	switch (interuptPin) {
	case 1:
		P1IE |= BIT3;				  // Re-enable interrupt after debouncing
		P1IFG &= ~BIT3;				  // Clear interrupt flag until next action
		break;
	case 2:
		P2IE |= BIT3;				  // Re-enable interrupt after debouncing
		P2IFG &= ~BIT3;				  // Clear interrupt flag until next action
		break;
	case 3:
		P3IE |= BIT0;				  // Re-enable interrupt after debouncing
		P3IFG &= ~BIT0;				  // Clear interrupt flag until next action
		break;
	case 4:
		P3IE |= BIT1;				  // Re-enable interrupt after debouncing
		P3IFG &= ~BIT1;				  // Clear interrupt flag until next action
		break;
	case 5:
		P1IE |= BIT1;				  // Re-enable interrupt after debouncing
		P1IFG &= ~BIT1;
		break;
	case 6:
		P1IE |= BIT2;				  // Re-enable interrupt after debouncing
		P1IFG &= ~BIT2;
	}
	if ((P2IES & BIT3) && (P1IES & BIT3) && (P3IES & BIT0) && (P3IES & BIT1) && (P1IES & BIT1) && (P1IES & BIT2))
		return;	  // Only work on presses
	//CHANGE FREQUENCY: IF FREQUENCY OR CHANGE PAGE IF PAGE:
	// interruptPins 1-4 are key pad
	if(interuptPin<5){
		//KEYPAD FUNCTION:
		if(key<10){
		    setSamplingFrequency();
		    if(triggerOn){
		    	selectModeChannel();
		    }else{
		    	TA3CCTL1=CCIE; //restart sampling
		    }

			clearMsgBox(1,1);
			char str[15];
			sprintf(str, "%d", key);
			drawString(2,LINE1, FONT_SM, "Samples: 408");
			drawString(80,LINE1, FONT_SM, "Freq: ");
			if(key==0){
				drawString(116,LINE1,FONT_SM,"25");
			}else{
				drawString(116,LINE1,FONT_SM,str);
			}
			drawString(128,LINE1,FONT_SM,"kHz");

		}else if(key<14){
			//select trigger channel if trigger mode: A-D
			if (!triggerOn)
				return;
			selectModeChannel();
			clearMsgBox(3,1);
			drawString(2,LINE3,FONT_SM,"Trigger Mode: ");
			switch(triggerType){
			case 1:
				drawString(84,LINE3,FONT_SM,"High");
				break;
			case 2:
				drawString(84,LINE3,FONT_SM,"Low");
				break;
			case 3:
				drawString(84,LINE3,FONT_SM,"Off");
				break;
			}
			drawString(124,LINE3,FONT_SM,"CH ");
			char str;
			switch(key){
			case 10:
				str='A';
				break;
			case 11:
				str='B';
				break;
			case 12:
				str='C';
				break;
			case 13:
				str='D';
				break;
			}
			drawCharSm(142, LINE3, str);
			clearMsgBox(4,1);
		}else if (key==15){
				//trigger mode select toggle
				triggerOn = 1- triggerOn;
				if (!triggerOn){
					clearMsgBox(3,1);
					clearMsgBox(4,1);
					drawString(2,LINE3,FONT_SM,"Trigger Mode: ");
					drawString(84,LINE3,FONT_SM,"Off");
				}else{
					drawString(2,LINE4,FONT_SM,"Trigger Select");
					channelA=channelB=channelC=channelD=0;
				}
		}
	}else if(interuptPin==5){
		//BUTTON P1.1 FUNCTIONALITY
		--page;
		if (page<1){
			page=1;
		}
		printChannel(page, 1);
		printChannel(page, 2);
		printChannel(page, 3);
		printChannel(page, 4);
		clearMsgBox(2, 1);
		char str[15];
		sprintf(str, "%d", page);
		drawString(2,LINE2,FONT_SM,"Page: ");
		drawString(38,LINE2,FONT_SM,str);
	}else{
		//BUTTON P1.2 FUNCTIONALITY
		page++;
		if (page>3){
			page=3;
		}
		printChannel(page, 1);
		printChannel(page, 2);
		printChannel(page, 3);
		printChannel(page, 4);
		clearMsgBox(2, 1);
		char str[15];
		sprintf(str, "%d", page);
		drawString(2,LINE2,FONT_SM,"Page: ");
		drawString(38,LINE2,FONT_SM,str);

	}
}

#pragma vector = TIMER3_A1_VECTOR
__interrupt void channel2Sampling_ISR() {
	switch (TA3IV) {
	case TA3IV_NONE:
		break;
	case TA3IV_TACCR1:
		TA3CCR1 += period0;
		if (channelCounter < samples) {
			channel1[channelCounter] = ((P2IN & BIT0) ? 1 : 0); //p2.0
			channel2[channelCounter] = ((P2IN & BIT1) ? 1 : 0); //p2.1
			channel3[channelCounter] = ((P2IN & BIT6) ? 1 : 0); //p2.6
			channel4[channelCounter] = ((P2IN & BIT7) ? 1 : 0); //p2.7
			channelCounter++;
		} else {
			page=1;
			printChannel(page, 1);
			printChannel(page, 2);
			printChannel(page, 3);
			printChannel(page, 4);
			clearMsgBox(2,1);
			drawString(2,LINE2,FONT_SM,"Page: 1");
			//reset
			channelCounter = 0;
			//take a break from sampling
			TA3CCTL1 = 0;
		}
		break;
	case TA3IV_TACCR2:
		break;
	case TA3IV_TACCR3:
		break;
	case TA3IV_TACCR4:
		break;
	default:
		break;
	}

}

void introScreen(void) {
	clearScreen(1);
	setColor(0xFFFF);
	//frame:
	drawLine(0, 0, 159, 0);
	drawLine(0, 127, 159, 127);
	drawLine(0, 0, 0, 127);
	drawLine(159, 0, 159, 127);
	//message box:
	drawLine(0, 88, 159, 88);
	//left margin:
	drawLine(20, 0, 20, 88);
	// chanels:
	drawString(2, 2, FONT_MD, "CH");
	drawString(12, 16, FONT_MD, "1");
	drawString(12, 32, FONT_MD, "2");
	drawString(12, 48, FONT_MD, "3");
	drawString(12, 64, FONT_MD, "4");
	//corner box:
	drawLine(112, 16, 159, 16);
	drawLine(112, 0, 112, 16);
	//axis intervals:
	drawLine(34, 85, 34, 88);
	drawLine(48, 85, 48, 88);
	drawLine(62, 85, 62, 88);
	drawLine(76, 85, 76, 88);
	drawLine(90, 85, 90, 88);
	drawLine(104, 85, 104, 88);
	drawLine(118, 85, 118, 88);
	drawLine(132, 85, 132, 88);
	drawLine(146, 85, 146, 88);
	drawLine(159, 85, 159, 88);

}
void init_samplingClock(void) {
	period0 = KILO;
	TA3CCR1 = period0;
	TA3CCTL1 = CCIE;
	TA3CTL = TASSEL__SMCLK | MC__CONTINUOUS | TACLR;
	drawString(2,LINE1, FONT_SM, "Samples: 408");
	drawString(80,LINE1, FONT_SM, "Freq: 1 kHz");
//	drawString(2,LINE2,FONT_SM,"Page: 1");
	drawString(2,LINE3,FONT_SM,"Trigger Mode: Off ");
}
void selectModeChannel(void){

	switch(key){
	case 10:
		channelA++;
		if(channelA==1){
			P2IFG &= ~(BIT0);        // clear p1.0 interrupt flag
			P2IE  |= BIT0;                   // ENABLE INTERRUPTS
			P2IES &= ~BIT0;                   // rising edge

		}else if(channelA==2){
			P2IFG &= ~(BIT0);        // clear p1.0 interrupt flag
			P2IE  |= BIT0;                   // ENABLE INTERRUPTS
			P2IES |= BIT0;                   // falling edge
		}else{
			P2IE &= ~BIT0;                   // DISABLE TRIGGER
			triggerOn=0;
		}
		triggerType=channelA;
		break;
	case 11:
		channelB++;
		if(channelB==1){
			P2IFG &= ~(BIT1);        // clear p1.0 interrupt flag
			P2IE  |= BIT1;                   // ENABLE INTERRUPTS
			P2IES &= ~BIT1;                   // rising edge

		}else if(channelB==2){
			P2IFG &= ~(BIT1);        // clear p1.0 interrupt flag
			P2IE  |= BIT1;                   // ENABLE INTERRUPTS
			P2IES |= BIT1;                   // falling edge

		}else{
			P2IE &= ~BIT1;                   // DISABLE TRIGGER
			triggerOn=0;
		}
		triggerType=channelB;
	     break;
	case 12:
		channelC++;
		if(channelC==1){
			P2IFG &= ~(BIT6);        // clear p1.0 interrupt flag
			P2IE  |= BIT6;                   // ENABLE INTERRUPTS
			P2IES &= ~BIT6;                   // rising edge
		}else if(channelC==2){
			P2IFG &= ~(BIT6);        // clear p1.0 interrupt flag
			P2IE  |= BIT6;                   // ENABLE INTERRUPTS
			P2IES |= BIT6;                   // falling edge
		}else{
			P2IE &= ~BIT6;                   // DISABLE TRIGGER
			triggerOn=0;
		}
		triggerType=channelC;
		break;
	case 13:
		channelD++;
		if(channelD==1){
			P2IFG &= ~(BIT7);        // clear p1.0 interrupt flag
			P2IE  |= BIT7;                   // ENABLE INTERRUPTS
			P2IES &= ~BIT7;                   // rising edge
		}else if(channelD==2){
			P2IFG &= ~(BIT7);        // clear p1.0 interrupt flag
			P2IE  |= BIT7;                   // ENABLE INTERRUPTS
			P2IES |= BIT7;                   // falling edge
		}else{
			P2IE &= ~BIT7;                   // DISABLE TRIGGER
			triggerOn=0;
		}
		triggerType=channelD;
		break;
	}

}

/*
 *  Needs to write data to the device using spi. We will only want to write to
 *  the device we wont worry the reads.
 */

void writeData(uint8_t data) {
//	P2OUT |= BIT3;
//	P2OUT |= BIT5;
	P3OUT &= ~(LCD_CS_PIN);					// enable CS
	P3OUT |= LCD_DC_PIN;					// select data
	UCB0TXBUF = data;
	while (UCB0STATW & UCBUSY)
		_nop();								// Keep transfering the data
	P3OUT |= LCD_CS_PIN;					// Disable chip
}

/*
 *	Needs to write commands to the device using spi
 */

void writeCommand(uint8_t command) {
//	P2OUT |= BIT3;
//	P2OUT &= ~BIT5;
	P3OUT &= ~(LCD_CS_PIN);					// enable CS
	P3OUT &= ~(LCD_DC_PIN);					// select data
	UCB0TXBUF = command;
	while (UCB0STATW & UCBUSY)				// Keep transfering the data
		_nop();
	P3OUT |= LCD_CS_PIN;						// Disable chip

}

void initMSP430(void) {

	/************************** PWM Backlight ******************************/

	P2DIR |= BIT4;
	P2SEL0 |= BIT4;
	P2SEL1 &= ~BIT4;
	TB0CCR0 = 511;
	TB0CCTL3 = OUTMOD_7;
	TB0CCR3 = 127;						//256;
	TB0CTL = TBSSEL__ACLK | MC__UP | TBCLR;

	/******************************** SPI **********************************/

	P3DIR |= LCD_DC_PIN | LCD_CS_PIN;			// DC and CS
	P1SEL0 |= LCD_MOSI_PIN | LCD_UCBCLK_PIN;      // MOSI and UCBOCLK
	P1SEL1 &= ~(LCD_MOSI_PIN | LCD_UCBCLK_PIN);

	UCB0CTLW0 |= UCSWRST;		// Reset UCB0

	/*
	 * UCBxCTLW0 	 - eUSCI_Bx Control Register 0
	 * UCSSEL__SMCLK - SMCLK in master mode
	 * UCCKPL 		 - Clocl polarity select
	 * UCMSB		 - MSB first select
	 * UCMST		 - Master mode select
	 * UCMODE_0      - eUSCI mode 3-pin SPI select
	 * UCSYNC		 -	Synchronous mode enable
	 */
	UCB0CTLW0 |= UCSSEL__SMCLK | UCCKPL | UCMSB | UCMST | UCMODE_0 | UCSYNC;

	UCB0BR0 |= 0x01;         // Clock = SMCLK/60
	UCB0BR1 = 0;
	UCB0CTL1 &= ~UCSWRST;    // Clear UCSWRST to release the eUSCI for operation
	PM5CTL0 &= ~LOCKLPM5;    // Unlock ports from power manager
	/***************************** timers ******************************/
	// Timers A2/3 are good for debouncing since they don't have external pins DEBOUNCING TIMER
	TA2CCR0 = 819;				// 25 ms * 32768 Hz = 819.2 ticks debounce delay
	TA2CTL = TASSEL__ACLK | MC__STOP | TACLR;// Configure debounce timer but don't start it

	//////////////////////////////////////////////////////////////////////
	/**************************** input *********************************/
	//////////////////////////////////////////////////////////////////////
	// Timer capture
	P2DIR &= ~(BIT0|BIT1|BIT6|BIT7);				// Set P2.0, P2.1, P2.6, P2.7 as input
	P2REN |= BIT0|BIT1|BIT6|BIT7;				    // Enable pull-up/down resistors
	P2OUT &= ~(BIT0|BIT1|BIT6|BIT7);				// Set p2.x resistor as pull-down

	P1DIR &= ~(BIT1|BIT2);
	P1REN |=  (BIT1|BIT2);
	P1OUT |=  (BIT1|BIT2);
	P1IES |=  (BIT1|BIT2); // make p1.1 & p1.2 interrupt happen on falling edge
	P1IFG &= ~(BIT1|BIT2);        // clear p1.1 & p1.2 interrupt flag
	P1IE  |=  (BIT1|BIT2);        // enable p1.1 & p1.2 interrupt





	__enable_interrupt();    // Set global interrupt enable bit in SR register

}
void setSamplingFrequency(void){
	switch(key){
	case 0:
		period0 = KILOTEN;
		break;
	case 1:
		period0 = KILO;
		break;
	case 2:
		period0 = KILOTWO;
		break;
	case 3:
		period0 = KILOTHREE;
		break;
	case 4:
		period0 = KILOFOUR;
		break;
	case 5:
		period0 = KILOFIVE;
		break;
	case 6:
		period0 = KILOSIX;
		break;
	case 7:
		period0 = KILOSEVEN;
		break;
	case 8:
		period0 = KILOEIGHT;
		break;
	case 9:
		period0 = KILONINE;
		break;
	default:
		period0 = KILO;
		break;
	}

}

void main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// kill the watchdog

	initMSP430();
	keypadInit();

	__delay_cycles(10);

	initLCD();
	introScreen();
	startup = 1; // This should be a clear flag for interrupts
	init_samplingClock();
	page=1;

	while (TRUE) {
		_nop();
	}
}
