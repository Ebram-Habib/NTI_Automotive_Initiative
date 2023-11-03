/*
 * main.c
 *
 *  Created on: Nov 1, 2023
 *      Author: Ebram Habib
 */

#include "std_types.h"
#include "TIMER1_int.h"
#include "GPIO_Int.h"
#include "GIE_int.h"

//void LED_On(void);

u8 g_edgeCount = 0;
u16 g_timeHigh = 0;
u16 g_timePeriod = 0;
u16 g_timePeriodPlusHigh = 0;

void APP_edgeProcessing(void);

u16 duty = 0;
u16 freq = 0;

TIMER1_INIT_CONFIG config = {
		TIMER1_COMPARE_OUTPUT_NON_PWM_MODE_OC1A_OC1B_DISCONNECTED,
		TIMER1_COMPARE_OUTPUT_FAST_PWM_MODE_OC1A_OC1B_CLEAR,
		TIMER1_COMPARE_OUTPUT_PHASE_CORRECT_PWM_MODE_OC1A_OC1B_DISCONNECTED,
		FCPU_DIVIDED_BY_64,
		TIMER1_NORMAL_MODE,
		0,
		0 };


int main()
{

	DIO_voidSetPinDirection(pPORTD, pin6, input);
	DIO_voidSetPinDirection(pPORTA, pin4, output);

	TIMER1_Init(&config);
	//		DIO_voidSetPinDirection(pPORTA, pin6, output);
	//		DIO_voidSetPinValue(pPORTA, pin6, LOGIC_LOW);
	//		GIE_Enable();
	//		TIMER1_SetCallBack(LED_On);
	//		TIMER1_SetDelayTimeMilliSec(&config, 1000);
	//		DIO_voidSetPinDirection(pPORTD, pin5, output);
	//		TIMER1_SetFastPWM(&config, 8);

	TIMER1_IntEnable(&config);

	TIMER1_SetCallBack(APP_edgeProcessing);
	//TIMER1_GetSignalFrequency();
	TIMER1_GetSignalDutyCycle();
	GIE_Enable();
	TIMER1_Start(&config);

	while(1)
	{
		if(g_edgeCount == 4)
		{
			TIMER1_IntDisable(&config); /* Disable timer Interrupts */
			GIE_Disable();
			g_edgeCount = 0;
			/* calculate the freq */
			freq = 1000000 / (g_timePeriodPlusHigh - g_timeHigh);;
			duty  = ((f32)(g_timePeriodPlusHigh-g_timePeriod) / (g_timePeriodPlusHigh - g_timeHigh)) * 100;
		}
		if((duty == 51))
		{
			DIO_voidSetPinValue(pPORTA, pin4, LOGIC_HIGH);
		}

	}

}

/* This is the call-back function */
void APP_edgeProcessing(void)
{
	g_edgeCount++;

	if(g_edgeCount == 1)
	{
		/*
		 * Clear the timer counter register to start measurements from the
		 * first detected rising edge
		 */
		TIMER1_ClearTimerValue();
		/* Detect falling edge */
		TIMER1_SetInputCaptureEdgeDetection(FALLING_EDGE);
	}
	else if(g_edgeCount == 2)
	{
		/* Store the High time value */
		g_timeHigh = TIMER1_GetInputCaptureValue();
		/* Detect rising edge */
		TIMER1_SetInputCaptureEdgeDetection(RISING_EDGE);
	}
	else if(g_edgeCount == 3)
	{
		/* Store the Period time value */
		g_timePeriod = TIMER1_GetInputCaptureValue();
		/* Detect falling edge */
		TIMER1_SetInputCaptureEdgeDetection(FALLING_EDGE);
	}
	else if(g_edgeCount == 4)
	{
		/* Store the Period time value + High time value */
		g_timePeriodPlusHigh = TIMER1_GetInputCaptureValue();
		/* Clear the timer counter register to start measurements again */
		TIMER1_ClearTimerValue();
		/* Detect rising edge */
		TIMER1_SetInputCaptureEdgeDetection(RISING_EDGE);
	}
}

//void LED_On(void)
//{
//	TIMER1_Stop(&config);
//
//	if(DIO_voidGetPinValue(pPORTA, pin6))
//	{
//		DIO_voidSetPinValue(pPORTA, pin6, LOGIC_LOW);
//	}
//	else
//	{
//		DIO_voidSetPinValue(pPORTA, pin6, LOGIC_HIGH);
//	}
//	TIMER1_SetDelayTimeMilliSec(&config, 1000);
//}
//
