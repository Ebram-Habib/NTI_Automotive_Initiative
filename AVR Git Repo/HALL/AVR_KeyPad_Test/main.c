/*
 * main.c
 *
 *  Created on: Oct 21, 2023
 *      Author: Ebram Habib
 */


#include "KeyPad.h"
#include "SevSeg.h"
#include <avr/delay.h>

int main()
{
	u8 num = 0;

	KEYPAD_Init();
	SevSeg_Init();

	while(1)
	{
		num = KEYPAD_Get_Pressed_Key();
		SevSeg_DisplayNum(num);
		_delay_ms(500);
	}
}
