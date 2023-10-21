/*
 * KeyPad.c
 *
 *  Created on: Oct 21, 2023
 *      Author: Ebram Habib
 */

#include "std_types.h"
#include "GPIO_Int.h"
#include "avr/delay.h"
#include "KeyPad.h"

void KEYPAD_Init(void)
{
	DIO_voidSetPinDirection(pPORTC, pin2, output);
	DIO_voidSetPinDirection(pPORTC, pin3, output);
	DIO_voidSetPinDirection(pPORTC, pin4, output);
	DIO_voidSetPinDirection(pPORTC, pin5, output);

	DIO_voidSetPinDirection(pPORTD, pin3, input);
	DIO_voidSetPinDirection(pPORTD, pin5, input);
	DIO_voidSetPinDirection(pPORTD, pin6, input);
	DIO_voidSetPinDirection(pPORTD, pin7, input);

	DIO_voidSetPinValue(pPORTC, pin2, low);
	DIO_voidSetPinValue(pPORTC, pin3, low);
	DIO_voidSetPinValue(pPORTC, pin4, low);
	DIO_voidSetPinValue(pPORTC, pin5, low);
}

u8 KEYPAD_Get_Pressed_Key(void)
{
	u8  i,j;
	u8 rows[]={5,4,3,2};
	u8 cols[]={7,6,5,3};

	while(1)
	{
		for(i = 0; i<SIZE; i++)
		{
			DIO_voidSetPinValue(pPORTC, rows[i], high);

			for(j = 0; j<SIZE; j++)
			{
				if(DIO_voidGetPinValue(pPORTD, cols[j]) == low)
				{
					return ((rows[i]*SIZE) + cols[j]+1);
				}
			}
		}
		DIO_voidSetPinValue(pPORTC, rows[i], low);
		_delay_ms(5);
	}


}
