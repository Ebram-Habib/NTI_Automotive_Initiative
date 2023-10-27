/*
 * main.c
 *
 *  Created on: Oct 22, 2023
 *      Author: Ebram Habib
 */

#include "std_types.h"
#include "EXTI_int.h"
#include "GPIO_Int.h"
#include "GIE_int.h"

void LedON(void);

int main()
{
	GIE_Enable();
	EXTI_voidEnable(EXTI_INT1_ID, FALLING_EDGE);
	DIO_voidSetPinDirection(pPORTD, 3, input);
	DIO_voidSetPinDirection(pPORTB, 7, output);
	DIO_voidSetPinValue(pPORTB, 7, low);
	EXTI_voidSetCallBack(LedON, EXTI_INT1_ID);

	while(1)
	{

	}
}

void LedON(void)
{
	static u8 u8_StatusFlag = 0;
	if(u8_StatusFlag == 0)
	{
		DIO_voidSetPinValue(pPORTB, 7, high);
		u8_StatusFlag = 1;
		EXTI_voidEnable(EXTI_INT1_ID, RISING_EDGE);
	}
	else
	{
		DIO_voidSetPinValue(pPORTB, 7, low);
		u8_StatusFlag = 0;
		EXTI_voidEnable(EXTI_INT1_ID, FALLING_EDGE);
	}
}
