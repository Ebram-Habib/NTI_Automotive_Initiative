/*
 * SevSeg.c
 *
 *  Created on: Oct 21, 2023
 *      Author: Ebram Habib
 */

#include "SevSeg.h"
#include "GPIO_Int.h"

void SevSeg_Init(void)
{
	/* Set pin directions for the seven segments and their enables pins */
	DIO_voidSetPinDirection(pPORTB, Pin0, output);
	DIO_voidSetPinDirection(pPORTB, pin1, output);
	DIO_voidSetPinDirection(pPORTB, pin2, output);
	DIO_voidSetPinDirection(pPORTB, pin4, output);
	/* enables */
	DIO_voidSetPinDirection(pPORTB, pin5, output);
	DIO_voidSetPinDirection(pPORTB, pin6, output);
	DIO_voidSetPinDirection(pPORTA, pin2, output);
	DIO_voidSetPinDirection(pPORTA, pin3, output);

	DIO_voidSetPinValue(pPORTB, Pin0, low);
	DIO_voidSetPinValue(pPORTB, pin1, low);
	DIO_voidSetPinValue(pPORTB, pin2, low);
	DIO_voidSetPinValue(pPORTB, pin4, low);

	DIO_voidSetPinValue(pPORTB, pin5, low);
	DIO_voidSetPinValue(pPORTB, pin6, low);
	DIO_voidSetPinValue(pPORTA, pin2, low);
	DIO_voidSetPinValue(pPORTA, pin3, low);
}
void SevSeg_DisplayNum(u8 u8_Num)
{
	switch(u8_Num)
	{
	case 0:
		DIO_voidSetPinValue(pPORTB, Pin0, 0);
		DIO_voidSetPinValue(pPORTB, pin1, 0);
		DIO_voidSetPinValue(pPORTB, pin2, 0);
		DIO_voidSetPinValue(pPORTB, pin4, 0);
		break;
	case 1:
		DIO_voidSetPinValue(pPORTB, Pin0, 1);
		DIO_voidSetPinValue(pPORTB, pin1, 0);
		DIO_voidSetPinValue(pPORTB, pin2, 0);
		DIO_voidSetPinValue(pPORTB, pin4, 0);
		break;
	case 2:
		DIO_voidSetPinValue(pPORTB, Pin0, 0);
		DIO_voidSetPinValue(pPORTB, pin1, 1);
		DIO_voidSetPinValue(pPORTB, pin2, 0);
		DIO_voidSetPinValue(pPORTB, pin4, 0);
		break;
	case 3:
		DIO_voidSetPinValue(pPORTB, Pin0, 1);
		DIO_voidSetPinValue(pPORTB, pin1, 1);
		DIO_voidSetPinValue(pPORTB, pin2, 0);
		DIO_voidSetPinValue(pPORTB, pin4, 0);
		break;
	case 4:
		DIO_voidSetPinValue(pPORTB, Pin0, 0);
		DIO_voidSetPinValue(pPORTB, pin1, 0);
		DIO_voidSetPinValue(pPORTB, pin2, 1);
		DIO_voidSetPinValue(pPORTB, pin4, 0);
		break;
	case 5:
		DIO_voidSetPinValue(pPORTB, Pin0, 1);
		DIO_voidSetPinValue(pPORTB, pin1, 0);
		DIO_voidSetPinValue(pPORTB, pin2, 1);
		DIO_voidSetPinValue(pPORTB, pin4, 0);
		break;
	case 6:
		DIO_voidSetPinValue(pPORTB, Pin0, 0);
		DIO_voidSetPinValue(pPORTB, pin1, 1);
		DIO_voidSetPinValue(pPORTB, pin2, 1);
		DIO_voidSetPinValue(pPORTB, pin4, 0);
		break;
	case 7:
		DIO_voidSetPinValue(pPORTB, Pin0, 1);
		DIO_voidSetPinValue(pPORTB, pin1, 1);
		DIO_voidSetPinValue(pPORTB, pin2, 1);
		DIO_voidSetPinValue(pPORTB, pin4, 0);
		break;
	case 8:
		DIO_voidSetPinValue(pPORTB, Pin0, 0);
		DIO_voidSetPinValue(pPORTB, pin1, 0);
		DIO_voidSetPinValue(pPORTB, pin2, 0);
		DIO_voidSetPinValue(pPORTB, pin4, 1);
		DIO_voidSetPortValue(pPORTB, 16);
		break;
	case 9:
		DIO_voidSetPinValue(pPORTB, Pin0, 1);
		DIO_voidSetPinValue(pPORTB, pin1, 0);
		DIO_voidSetPinValue(pPORTB, pin2, 0);
		DIO_voidSetPinValue(pPORTB, pin4, 1);
		break;
	}
}
