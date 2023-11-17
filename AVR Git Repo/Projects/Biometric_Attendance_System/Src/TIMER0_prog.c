/*
 * TIMER0_prog.c
 *
 *  Created on: Oct 27, 2023
 *      Author: Ebram Habib
 */

#include "std_types.h"
#include "TIMER0_config.h"
#include "TIMER0_int.h"
#include "TIMER0_priv.h"
#include <avr/interrupt.h>

s32 overFlowCounter = 0;
u8 remCounter = 0;

void(*ptrCallBack)(void) = NULL_PTR;

void Timer0_Init(const TIMER0_INIT_CONFIG* Config_Ptr)
{
	switch(Config_Ptr->Mode)
	{
	case TIMER0_NORMAL_MODE:
		TCCR0_REG->bits.FOC0_BIT = LOGIC_HIGH;
		TCCR0_REG->bits.COM01_BIT = (Config_Ptr->Compare_output_Non_PWM>>1);
		TCCR0_REG->bits.COM00_BIT = (Config_Ptr->Compare_output_Non_PWM>>0);
		OCR0_REG = Config_Ptr->TIMER0_COMPARE_VALUE;
		break;
	case TIMER0_PHASE_CORRECT_PWM_MODE:
		TCCR0_REG->bits.FOC0_BIT = LOGIC_LOW;
		TCCR0_REG->bits.COM01_BIT = (Config_Ptr->Compare_output_Phase_Correct_PWM>>1);
		TCCR0_REG->bits.COM00_BIT = (Config_Ptr->Compare_output_Phase_Correct_PWM>>0);
		//OCR0_REG = Config_Ptr->TIMER0_COMPARE_VALUE;
		break;
	case TIMER0_CTC_MODE:
		TCCR0_REG->bits.FOC0_BIT = LOGIC_HIGH;
		TCCR0_REG->bits.COM01_BIT = (Config_Ptr->Compare_output_Non_PWM>>1);
		TCCR0_REG->bits.COM00_BIT = (Config_Ptr->Compare_output_Non_PWM>>0);
		OCR0_REG = Config_Ptr->TIMER0_COMPARE_VALUE;
		break;
	case TIMER0_FAST_PWM_MODE:
		TCCR0_REG->bits.FOC0_BIT = LOGIC_LOW;
		TCCR0_REG->bits.COM01_BIT = (Config_Ptr->Compare_output_Fast_PWM>>1);
		TCCR0_REG->bits.COM00_BIT = (Config_Ptr->Compare_output_Fast_PWM>>0);
		//OCR0_REG = Config_Ptr->TIMER0_COMPARE_VALUE;
		break;
	}
	TCNT0_REG = Config_Ptr->TIMER0_INITIAL_VALUE;
	TCCR0_REG->bits.WGM01_BIT = (Config_Ptr->Mode>>1);
	TCCR0_REG->bits.WGM00_BIT = (Config_Ptr->Mode>>0);
	//TCCR0_REG->FULL_REG = ((TCCR0_REG->FULL_REG & CLOCK_SELECT_MASK) | (Config_Ptr->Clock_Select));
}
void Timer0_Start(const TIMER0_INIT_CONFIG* Config_Ptr)
{
	TCCR0_REG->FULL_REG = ((TCCR0_REG->FULL_REG & CLOCK_SELECT_MASK) | (Config_Ptr->Clock_Select));
}
void Timer0_Stop(const TIMER0_INIT_CONFIG* Config_Ptr)
{
	TCCR0_REG->FULL_REG = ((TCCR0_REG->FULL_REG & CLOCK_SELECT_MASK) | (NO_CLOCK));
}
u8 Timer0_GetCounts(void)
{
	return TCNT0_REG;
}
void Timer0_SetDelayTimeMilliSec(const TIMER0_INIT_CONFIG* Config_Ptr, u32 copy_u32TimeMS)
{
	/* Assuming we are using 16MHz FCPU and Prescaler 1024  Tick time = 2 Micro seconds */
	switch(Config_Ptr->Mode)
	{
	case TIMER0_NORMAL_MODE:
		overFlowCounter = (((copy_u32TimeMS * 1000)/TIMER0_TICK_TIME) / TOP_VALUE);
		remCounter = (u8)(((copy_u32TimeMS * 1000)/TIMER0_TICK_TIME) % TOP_VALUE);
		Timer0_IntEnable(Config_Ptr);
		Timer0_Start(Config_Ptr);
		break;
	case TIMER0_CTC_MODE:

		break;

	}
}
void Timer0_IntEnable(const TIMER0_INIT_CONFIG* Config_Ptr)
{
	if(Config_Ptr->Mode == TIMER0_NORMAL_MODE)
	{
		TIMSK_REG->bits.TOIE0_BIT = LOGIC_HIGH;
	}
	else if (Config_Ptr->Mode == TIMER0_CTC_MODE)
	{
		TIMSK_REG->bits.OCIE0_BIT = LOGIC_HIGH;
	}
	else
	{
		//return error;
	}
}
void Timer0_IntDisable(const TIMER0_INIT_CONFIG* Config_Ptr)
{
	if(Config_Ptr->Mode == TIMER0_NORMAL_MODE)
		{
			TIMSK_REG->bits.TOIE0_BIT = LOGIC_LOW;
		}
		else if (Config_Ptr->Mode == TIMER0_CTC_MODE)
		{
			TIMSK_REG->bits.OCIE0_BIT = LOGIC_LOW;
		}
		else
		{
			//return error;
		}
}
void TIMER0_clearTimerValue(void)
{
	TCNT0_REG = 0;
}

void Timer0_SetCallBack(void(*ptrfn)(void))
{
	ptrCallBack = ptrfn;
}
void Timer0_SetFastPWM(const TIMER0_INIT_CONFIG* Config_Ptr, u8 duty)
{
	/* pwm freq = FCPU/(prescaler*256) */

	/* duty cycle */
	OCR0_REG = (u8)((duty*255)/100);

}
void Timer0_SetPhaseCorrectPWM(const TIMER0_INIT_CONFIG* Config_Ptr, u8 duty);

ISR(TIMER0_OVF_vect)
{
	overFlowCounter--;

	if(overFlowCounter == 0)
	{
		TCNT0_REG = (256 - remCounter);
	}
	if((ptrCallBack != NULL_PTR) && (overFlowCounter == -1))
	{
		(*ptrCallBack)();
	}
}

ISR(TIMER0_COMP_vect)
{
	if(ptrCallBack != NULL_PTR)
	{
		(*ptrCallBack)();
	}
}
