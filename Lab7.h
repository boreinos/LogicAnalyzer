/*
 * Lab7.h
 *
 *  Created on: Apr 9, 2016
 *      Author: Boris
 */

#ifndef LAB7_H_
#define LAB7_H_
/*#include "color.h"*/
int frequency;

#define samples 403
uint8_t channel1[samples];
uint8_t channel2[samples];
uint8_t channel3[samples];
uint8_t channel4[samples];

uint8_t channelA;
uint8_t channelB;
uint8_t channelC;
uint8_t channelD;

uint8_t triggerOn;
uint8_t triggerType;
uint8_t page;

/*************************/
#define TIMER_CFG_STOP TASSEL__ACLK | MC__STOP | TACLR;
#define TIMER_CFG_UP   TASSEL__ACLK | MC__UP   | TACLR;

//frequencies:
#define KILO  109 //1 ms * 1000000 = 1000
#define KILOTWO 500
#define KILOTHREE 333
#define KILOFOUR 250
#define KILOFIVE 200//5Khz 0.00002*1000000= 200
#define KILOSIX 167
#define KILOSEVEN 143
#define KILOEIGHT 125
#define KILONINE 111
#define KILOTEN 40

#define LINE1 90
#define LINE2 99
#define LINE3 108
#define LINE4 117



volatile unsigned int channelCounter, period0;
volatile unsigned int interuptPin, key;




#endif /* LAB7_H_ */
