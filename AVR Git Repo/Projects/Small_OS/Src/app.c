/*
 * app.c
 *
 *  Created on: Nov 4, 2023
 *      Author: Ebram Habib
 */


#include "std_types.h"
#include "GPIO_Int.h"
#include "GIE_int.h"
#include "TIMER0_int.h"

/* Function Prototypes */
void scheduler(void);
void task1(void);
void task2(void);
void task3(void);

/* Global Variables */
void (*ptrfn[3])(void) = {NULL_PTR,NULL_PTR,NULL_PTR};
volatile u8 counter = 0;

/* Timer0 configuration */
TIMER0_INIT_CONFIG config = {
		TIMER0_COMPARE_OUTPUT_NON_PWM_MODE_OC0_DISCONNECTED,
		TIMER0_COMPARE_OUTPUT_FAST_PWM_MODE_OC0_CLEAR,
		TIMER0_COMPARE_OUTPUT_PHASE_CORRECT_PWM_MODE_OC0_DISCONNECTED,
		FCPU_DIVIDED_BY_1024,
		TIMER0_NORMAL_MODE,
		0,
		0 };


int main()
{
	u8 i = 0;


	/* LEDs initialization */
	DIO_voidSetPinDirection(pPORTA, pin4, output); /* Green LED */
	DIO_voidSetPinDirection(pPORTA, pin5, output); /* Blue LED */
	DIO_voidSetPinDirection(pPORTB, pin7, output); /* RED LED */

	DIO_voidSetPinValue(pPORTA, pin4, LOGIC_LOW);
	DIO_voidSetPinValue(pPORTA, pin5, LOGIC_LOW);
	DIO_voidSetPinValue(pPORTB, pin7, LOGIC_LOW);

	/* Push Button initialization with internal pull-up */
	DIO_voidSetPinDirection(pPORTD, pin7, input); /* Push Button 1 */
	DIO_voidSetPinValue(pPORTD, pin7, LOGIC_HIGH);

	Timer0_Init(&config);

	Timer0_SetCallBack(scheduler);
	GIE_Enable();
	Timer0_SetDelayTimeMilliSec(&config, 500);


	while(1)
	{
		for(i=0;i<3;i++)
		{
			if(ptrfn[i] != NULL_PTR)
			{
				(*ptrfn[i])();
			}
		}
	}
}

void task1(void)
{
	/* Mechanism to toggle the RED LED */
	if(DIO_voidGetPinValue(pPORTB, pin7))
	{
		DIO_voidSetPinValue(pPORTB, pin7, LOGIC_LOW);
	}
	else
	{
		DIO_voidSetPinValue(pPORTB, pin7, LOGIC_HIGH);
	}
	/* Set the task status to IDEL */
	ptrfn[0] = NULL_PTR;
}

void task2(void)
{
	/* Checking if the button is pressed */
	if(!(DIO_voidGetPinValue(pPORTD, pin7)))
	{
		/* Mechanism to toggle the Blue LED */
		if(DIO_voidGetPinValue(pPORTA, pin5))
		{
			DIO_voidSetPinValue(pPORTA, pin5, LOGIC_LOW);
		}
		else
		{
			DIO_voidSetPinValue(pPORTA, pin5, LOGIC_HIGH);
		}
	}
	/* Set the task status to IDEL */
	ptrfn[1] = NULL_PTR;
}
void task3(void)
{
	/* Mechanism to toggle the Green LED */
	if(DIO_voidGetPinValue(pPORTA, pin4))
	{
		DIO_voidSetPinValue(pPORTA, pin4, LOGIC_LOW);
	}
	else
	{
		DIO_voidSetPinValue(pPORTA, pin4, LOGIC_HIGH);
	}
	/* Set the task status to IDEL */
	ptrfn[2] = NULL_PTR;
}

void scheduler(void)
{
	counter++;
	switch(counter)
	{
	case 1:
		ptrfn[0] = task1;
		ptrfn[1] = task2;		/* all tasks should run at the beginning */
		ptrfn[2] = task3;
		break;
	case 2:
		ptrfn[1] = task2;
		break;
	case 3:
		ptrfn[0] = task1;
		ptrfn[1] = task2;
		break;
	case 4:
		ptrfn[1] = task2;
		break;
	case 5:
		ptrfn[0] = task1;
		ptrfn[1] = task2;
		break;
	case 6:
		ptrfn[1] = task2;
		counter = 0;
		break;
	}
	Timer0_SetDelayTimeMilliSec(&config, 500);
}
