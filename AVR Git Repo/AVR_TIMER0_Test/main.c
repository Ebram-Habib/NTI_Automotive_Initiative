/*
 * main.c
 *
 *  Created on: Oct 27, 2023
 *      Author: Ebram Habib
 */

#include "std_types.h"
#include "TIMER0_int.h"
#include "TIMER0_config.h"
#include "GPIO_Int.h"
#include "GIE_int.h"

void LED_On(void);

TIMER0_INIT_CONFIG config = {TIMER0_COMPARE_OUTPUT_NON_PWM_MODE_OC0_DISCONNECTED,TIMER0_COMPARE_OUTPUT_FAST_PWM_MODE_OC0_DISCONNECTED,TIMER0_COMPARE_OUTPUT_PHASE_CORRECT_PWM_MODE_OC0_DISCONNECTED,FCPU_DIVIDED_BY_1024,TIMER0_NORMAL_MODE, 0, 0 };


int main()
{
	GIE_Enable();
	Timer0_Init(&config);
	DIO_voidSetPinDirection(pPORTA, pin6, output);
	DIO_voidSetPinValue(pPORTA, pin6, LOGIC_LOW);
	Timer0_SetCallBack(LED_On);
	Timer0_SetDelayTimeMilliSec(&config, 1000);

	while(1)
	{

	}

}
void LED_On(void)
{
	Timer0_Stop(&config);

	if(DIO_voidGetPinValue(pPORTA, pin6))
	{
		DIO_voidSetPinValue(pPORTA, pin6, LOGIC_LOW);
	}
	else
	{
		DIO_voidSetPinValue(pPORTA, pin6, LOGIC_HIGH);
	}
	Timer0_SetDelayTimeMilliSec(&config, 1000);
}
