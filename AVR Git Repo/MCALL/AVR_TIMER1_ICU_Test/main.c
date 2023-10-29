/*
 * main.c
 *
 *  Created on: Oct 28, 2023
 *      Author: Ebram Habib
 */

#include "std_types.h"
#include "TIMER1_int.h"
#include "GIE_int.h"
#include "GPIO_Int.h"
#include "LCD_int.h"
#include "TIMER0_int.h"
//#include <avr/io.h>

u8 g_edgeCount = 0;
u16 g_timeHigh = 0;
u16 g_timePeriod = 0;
u16 g_timePeriodPlusHigh = 0;

void APP_edgeProcessing(void);

u16 dutyVal = 0;

TIMER0_INIT_CONFIG TIMER0_config = {
		TIMER0_COMPARE_OUTPUT_NON_PWM_MODE_OC0_DISCONNECTED,
		TIMER0_COMPARE_OUTPUT_FAST_PWM_MODE_OC0_SET,
		TIMER0_COMPARE_OUTPUT_PHASE_CORRECT_PWM_MODE_OC0_DISCONNECTED,
		FCPU_DIVIDED_BY_1024,
		TIMER0_FAST_PWM_MODE,
		0,
		0 };

TIMER1_INIT_CONFIG TIMER1_config = {
		TIMER1_COMPARE_OUTPUT_NON_PWM_MODE_OC1A_OC1B_DISCONNECTED,
		TIMER1_COMPARE_OUTPUT_FAST_PWM_MODE_OC1A_OC1B_SET,
		TIMER1_COMPARE_OUTPUT_PHASE_CORRECT_PWM_MODE_OC1A_OC1B_DISCONNECTED,
		FCPU_DIVIDED_BY_1024,
		TIMER1_NORMAL_MODE,
		0,
		0
};


//void PWM_Timer0_Start(u8 duty_cycle);


int main()
{
	u32 freq = 0;
	u32 duty = 0;

	DIO_voidSetPinDirection(pPORTB, pin3, output);
	DIO_voidSetPinValue(pPORTB, pin3, LOGIC_LOW);

//	DIO_voidSetPinDirection(pPORTD, pin5, output);
//	DIO_voidSetPinValue(pPORTD, pin5, LOGIC_LOW);

	DIO_voidSetPinDirection(pPORTD, pin6, input);

	GIE_Enable();
	H_LCD_void_Init();

	TIMER0_Init(&TIMER0_config);
	TIMER0_SetFastPWM(&TIMER0_config, 75);
	//PWM_Timer0_Start(65);

	TIMER1_Init(&TIMER1_config);
	TIMER1_IntEnable(&TIMER1_config);

	TIMER1_SetCallBack(APP_edgeProcessing);
	//TIMER1_GetSignalFrequency();
	TIMER1_GetSignalDutyCycle();
	TIMER1_Start(&TIMER1_config);
	TIMER0_Start(&TIMER0_config);

	while(1)
	{
		if(g_edgeCount == 4)
		{
			TIMER1_IntDisable(&TIMER1_config); /* Disable timer Interrupts */
			GIE_Disable();
			g_edgeCount = 0;
			H_LCD_void_gotoXY(0, 0);
			H_LCD_void_sendString("freq = ");
			/* calculate the freq */
			freq = 1000000 / (g_timePeriodPlusHigh - g_timeHigh);;
			duty  = ((f32)(g_timePeriodPlusHigh-g_timePeriod) / (g_timePeriodPlusHigh - g_timeHigh)) * 100;
			/* display the freq on LCD screen */
			H_LCD_void_sendIntNum(freq);
			H_LCD_void_sendString(" Hz");
			H_LCD_void_gotoXY(1, 0);
			H_LCD_void_sendString("duty = ");
			H_LCD_void_sendIntNum(duty);
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
/*
void PWM_Timer0_Start(u8 duty_cycle)
{
	TCNT0 = 0; //Set Timer Initial value

	OCR0  = duty_cycle; // Set Compare Value

	DDRB  = DDRB | (1<<PB3); //set PB3/OC0 as output pin --> pin where the PWM signal is generated from MC.

	/* Configure timer control register
 * 1. Fast PWM mode FOC0=0
 * 2. Fast PWM Mode WGM01=1 & WGM00=1
 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
 *//*
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);
}
  */
