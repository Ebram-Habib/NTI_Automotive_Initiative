/*
 * app.c
 *
 *  Created on: Nov 9, 2023
 *      Author: Ebram Habib
 */

#include "std_types.h"
#include "GIE_int.h"
#include "DCMOTOR_int.h"
#include "LM35_SENSOR_int.h"
#include "LCD_int.h"

int main()
{
	u8 temp = 0;

	DcMotor_Init();			/* initialize DCMotor driver */
	H_LCD_void_Init();		/* initialize LCD driver */
	LM35_SENSOR_init();		/* initialize LM35 Temperature sensor driver */

	GIE_Enable();			/* Enabling the globe interrupts to use it with ADC function */

	/* Display this string "Temp =   C" only once on LCD at the second row */
	H_LCD_void_gotoXY(1,3);
	H_LCD_void_sendString("Temp =    C");

	while(1)
	{

		temp = LM35_SENSOR_getTemperature();

		/* Display the temperature value every time at same position */
		H_LCD_void_gotoXY(1,10);
		if(temp >= 100)
		{
			H_LCD_void_sendIntNum(temp);
		}
		else
		{
			H_LCD_void_sendIntNum(temp);
			/* In case the digital value is two or one digits print space in the next digit place */
			LCD_displayCharacter(' ');
		}

		if(temp < 20)
		{
			H_LCD_void_gotoXY(0,3);
			H_LCD_void_sendString("Fan is OFF    ");
			DcMotor_OFF();
		}
		else if((temp >= 25) && (temp <= 35))
		{
			H_LCD_void_gotoXY(0,3);
			H_LCD_void_sendString("Fan is ON 50%");
			DcMotor_ON(50);		/* Let the motor rotate with 50% duty cycle */
		}
		else if(temp > 35)
		{
			H_LCD_void_gotoXY(0,3);
			H_LCD_void_sendString("Fan is ON 80%");
			DcMotor_ON(80);		/* Let the motor rotate with 80% duty cycle */
		}
	}
}
