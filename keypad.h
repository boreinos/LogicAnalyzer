/*
 * keypad1.h
 *
 *  Created on: Mar 2, 2016
 *      Author: breinosa
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

void keypadInit(void);
unsigned int scanKeyPad(void);
void resetPins(void);

#endif /* KEYPAD_H_ */
