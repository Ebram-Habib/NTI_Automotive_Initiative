/*
 * app.c
 *
 *  Created on: Nov 5, 2023
 *      Author: Ebram Habib
 */

#include "std_types.h"
#include "GPIO_Int.h"
#include "KeyPad.h"
#include "LCD_int.h"
#include "TIMER0_int.h"
#include "TIMER1_int.h"
#include "GIE_int.h"

u8 dutyVal = 0;
u8 flag =0;

TIMER0_INIT_CONFIG config = {
		TIMER0_COMPARE_OUTPUT_NON_PWM_MODE_OC0_DISCONNECTED,
		TIMER0_COMPARE_OUTPUT_FAST_PWM_MODE_OC0_CLEAR,
		TIMER0_COMPARE_OUTPUT_PHASE_CORRECT_PWM_MODE_OC0_DISCONNECTED,
		TIMER0_FCPU_DIVIDED_BY_1024,
		TIMER0_FAST_PWM_MODE,
		0,
		0 };

TIMER1_INIT_CONFIG TIMER1_config = {
		TIMER1_COMPARE_OUTPUT_NON_PWM_MODE_OC1A_OC1B_DISCONNECTED,
		TIMER1_COMPARE_OUTPUT_FAST_PWM_MODE_OC1A_OC1B_SET,
		TIMER1_COMPARE_OUTPUT_PHASE_CORRECT_PWM_MODE_OC1A_OC1B_DISCONNECTED,
		TIMER1_FCPU_DIVIDED_BY_64,
		TIMER1_NORMAL_MODE,
		0,
		0
};

void delayCallBack(void);
void delayMilliSec(u32 millisec);

int main()
{
	u8 i,digit=0;

	/* Initialization */
	DIO_voidSetPinDirection(pPORTB, pin3, output);

	Timer0_Init(&config);
	TIMER1_Init(&TIMER1_config);
	H_LCD_void_Init();
	KEYPAD_Init();
	Timer0_Start(&config);
	GIE_Enable();

	while(1)
	{
		dutyVal = 0;
		H_LCD_void_clearDisplay();
		H_LCD_void_gotoXY(0, 0);
		H_LCD_void_sendString("Plz Enter DutyCycle:");
		H_LCD_void_gotoXY(1, 4);
		H_LCD_void_sendData('%');
		H_LCD_void_gotoXY(1, 0);
		for(i=0 ; i<3 ; i++)
		{
			digit = KEYPAD_Get_Pressed_Key();
			H_LCD_void_sendData(digit+'0');
			dutyVal = ((dutyVal*10) + digit);
			delayMilliSec(250);
		}
		Timer0_SetFastPWM(&config, dutyVal);
		delayMilliSec(500);
	}
}

void delayCallBack(void)
{
	flag = 1;
}

void delayMilliSec(u32 millisec)
{
	TIMER1_SetCallBack(delayCallBack);
	TIMER1_ClearTimerValue();
	TIMER1_SetDelayTimeMilliSec(&TIMER1_config, millisec);
	while(flag == 0);
	flag = 0;
}
