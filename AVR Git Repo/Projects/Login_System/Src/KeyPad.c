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
	/* Rows */
	DIO_voidSetPinDirection(pPORTC, Pin0, output);
	DIO_voidSetPinDirection(pPORTC, pin1, output);
	DIO_voidSetPinDirection(pPORTC, pin2, output);
	DIO_voidSetPinDirection(pPORTC, pin3, output);

	/* Columns */
	DIO_voidSetPinDirection(pPORTC, pin4, input);
	DIO_voidSetPinDirection(pPORTC, pin5, input);
	DIO_voidSetPinDirection(pPORTC, pin6, input);
	DIO_voidSetPinDirection(pPORTC, pin7, input);

	DIO_voidSetPinValue(pPORTC, Pin0, high);
	DIO_voidSetPinValue(pPORTC, pin1, high);
	DIO_voidSetPinValue(pPORTC, pin2, high);
	DIO_voidSetPinValue(pPORTC, pin3, high);

//	DIO_voidSetPinValue(pPORTC, pin4, high);
//	DIO_voidSetPinValue(pPORTC, pin5, high);
//	DIO_voidSetPinValue(pPORTC, pin6, high);
//	DIO_voidSetPinValue(pPORTC, pin7, high);
}

u8 KEYPAD_Get_Pressed_Key(void)
{
	u8  i,j;
	u8 rows[]={3,2,1,0};
	u8 cols[]={4,5,6,7};

	while(1)
	{

		for(i = 0; i<SIZE; i++)
		{
			DIO_voidSetPinValue(pPORTC, rows[i], low);

			for(j = 0; j<SIZE; j++)
			{
				if(DIO_voidGetPinValue(pPORTC, cols[j]) == low)
				{
					_delay_ms(30);
					if(DIO_voidGetPinValue(pPORTC, cols[j]) == low)
					{
						return ((i*SIZE) + (j));
					}
				}
			}
			DIO_voidSetPinValue(pPORTC, rows[i], high);
			_delay_ms(5);
		}


		//		for(i = 0; i<SIZE; i++)
			//		{
		//			DIO_voidSetPinValue(pPORTD, rows[i], low);
		//
		//			for(j = 0; j<SIZE; j++)
		//			{
		//				if(DIO_voidGetPinValue(pPORTD, cols[j]) == low)
		//				{
		//					_delay_ms(30);
		//					if(DIO_voidGetPinValue(pPORTD, cols[j]) == low)
		//					{
		//						return ((i*SIZE) + (j));
		//					}
		//				}
		//			}
		//			DIO_voidSetPinValue(pPORTD, rows[i], high);
		//			_delay_ms(5);
		//		}

	}


}
