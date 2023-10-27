/*
 * main.c
 *
 *  Created on: Oct 24, 2023
 *      Author: Ebram Habib
 */

#include "GPIO_Int.h"
#include "ADC_int.h"
#include "ADC_config.h"
#include "LCD_int.h"
#include "GIE_int.h"

u16 copy_result = 0;

void valueUpdate(u16 val);

int main()
{

	u8 voltVal = 0;
	DIO_voidSetPinDirection(pPORTA, Pin0, input);

	ADC_INIT_CONFIG config = {ADC_INT_ENABLE, AVCC, DIVISION_FACTOR_8, LEFT_ADJUST};
	GIE_Enable();

	H_LCD_void_Init();
	ADC_Init(&config);

	H_LCD_void_sendString("Reading: ");



	while(1)
	{

		//ADC_getDigitalValueAsynchCallBack(ADC0, valueUpdate);
		//copy_result = ADC_getDigitalValueSynchNonBlocking(ADC0);
/*
		if(copy_result != 0)
		{
			//voltVal = (u8)(((u32)copy_result * 5)/1023);
			H_LCD_void_gotoXY(0, 14);
			H_LCD_void_sendIntNum(copy_result);
		}
*/
	}
}

void valueUpdate(u16 val)
{

	copy_result = val;
}
