/*
 * ports.h
 */

#ifndef PORTS_H_
#define PORTS_H_

#include <msp430.h>
#include <stdint.h>

typedef enum { FALSE, TRUE } bool;

#define LCD_UCBCLK_PIN BIT4 	// clock
#define LCD_MOSI_PIN BIT6 		// data out
#define GPIO_PIN (BIT0|BIT1)  // set this pins to GPIO

#define LCD_CS_PIN BIT3 		// chip select
#define LCD_DC_PIN BIT6 		// data/command

/*
 *  Function definitions
 */

void initMSP430(void);
void introScreen(void);
void writeData(uint8_t data);
void writeCommand(uint8_t command);


#endif /* PORTS_H_ */
