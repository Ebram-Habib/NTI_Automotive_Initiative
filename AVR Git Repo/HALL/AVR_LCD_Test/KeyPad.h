/*
 * KeyPad.h
 *
 *  Created on: Oct 21, 2023
 *      Author: Ebram Habib
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "std_types.h"

#define SIZE	4

void KEYPAD_Init(void);
u8 KEYPAD_Get_Pressed_Key(void);

#endif /* KEYPAD_H_ */
