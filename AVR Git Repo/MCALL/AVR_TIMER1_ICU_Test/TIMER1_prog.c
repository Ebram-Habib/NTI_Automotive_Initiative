/*
 * TIMER1_prog.c
 *
 *  Created on: Oct 28, 2023
 *      Author: Ebram Habib
 */

#include "std_types.h"
#include "TIMER1_config.h"
#include "TIMER1_int.h"
#include "TIMER1_priv.h"
#include <avr/interrupt.h>

s32 timer1OverFlowCounter = 0;
u16 timer1RemCounter = 0;

void(*timer1PtrCallBack)(void) = NULL_PTR;

void TIMER1_Init(const TIMER1_INIT_CONFIG* Config_Ptr)
{
	switch(Config_Ptr->Mode)
	{
	case TIMER1_NORMAL_MODE:
		TCCR1A_REG->bits.FOC1A_BIT = LOGIC_LOW;
		TCCR1A_REG->bits.FOC1B_BIT = LOGIC_LOW;
		TCCR1A_REG->bits.COM1A1_BIT = (Config_Ptr->Compare_output_Non_PWM>>1);
		TCCR1A_REG->bits.COM1A0_BIT = (Config_Ptr->Compare_output_Non_PWM>>0);
		TCCR1A_REG->bits.COM1B1_BIT = (Config_Ptr->Compare_output_Non_PWM>>1);
		TCCR1A_REG->bits.COM1B0_BIT = (Config_Ptr->Compare_output_Non_PWM>>0);
		OCR1AH_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		OCR1AL_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		OCR1BH_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		OCR1BL_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		break;
	case TIMER1_PHASE_CORRECT_PWM_8bIT_MODE:
		TCCR1A_REG->bits.FOC1A_BIT = LOGIC_LOW;
		TCCR1A_REG->bits.FOC1B_BIT = LOGIC_LOW;
		TCCR1A_REG->bits.COM1A1_BIT = (Config_Ptr->Compare_output_Phase_Correct_PWM>>1);
		TCCR1A_REG->bits.COM1A0_BIT = (Config_Ptr->Compare_output_Phase_Correct_PWM>>0);
		TCCR1A_REG->bits.COM1B1_BIT = (Config_Ptr->Compare_output_Phase_Correct_PWM>>1);
		TCCR1A_REG->bits.COM1B0_BIT = (Config_Ptr->Compare_output_Phase_Correct_PWM>>0);
		OCR1AH_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		OCR1AL_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		OCR1BH_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		OCR1BL_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		break;
	case TIMER1_PHASE_CORRECT_PWM_9bIT_MODE:
		TCCR1A_REG->bits.FOC1A_BIT = LOGIC_LOW;
		TCCR1A_REG->bits.FOC1B_BIT = LOGIC_LOW;
		TCCR1A_REG->bits.COM1A1_BIT = (Config_Ptr->Compare_output_Phase_Correct_PWM>>1);
		TCCR1A_REG->bits.COM1A0_BIT = (Config_Ptr->Compare_output_Phase_Correct_PWM>>0);
		TCCR1A_REG->bits.COM1B1_BIT = (Config_Ptr->Compare_output_Phase_Correct_PWM>>1);
		TCCR1A_REG->bits.COM1B0_BIT = (Config_Ptr->Compare_output_Phase_Correct_PWM>>0);
		OCR1AH_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		OCR1AL_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		OCR1BH_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		OCR1BL_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		break;
	case TIMER1_PHASE_CORRECT_PWM_10bIT_MODE:
		TCCR1A_REG->bits.FOC1A_BIT = LOGIC_LOW;
		TCCR1A_REG->bits.FOC1B_BIT = LOGIC_LOW;
		TCCR1A_REG->bits.COM1A1_BIT = (Config_Ptr->Compare_output_Phase_Correct_PWM>>1);
		TCCR1A_REG->bits.COM1A0_BIT = (Config_Ptr->Compare_output_Phase_Correct_PWM>>0);
		TCCR1A_REG->bits.COM1B1_BIT = (Config_Ptr->Compare_output_Phase_Correct_PWM>>1);
		TCCR1A_REG->bits.COM1B0_BIT = (Config_Ptr->Compare_output_Phase_Correct_PWM>>0);
		OCR1AH_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		OCR1AL_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		OCR1BH_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		OCR1BL_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		break;
	case TIMER1_CTC_OCR1A_MODE:
		TCCR1A_REG->bits.FOC1A_BIT = LOGIC_LOW;
		TCCR1A_REG->bits.FOC1B_BIT = LOGIC_LOW;
		TCCR1A_REG->bits.COM1A1_BIT = (Config_Ptr->Compare_output_Non_PWM>>1);
		TCCR1A_REG->bits.COM1A0_BIT = (Config_Ptr->Compare_output_Non_PWM>>0);
		TCCR1A_REG->bits.COM1B1_BIT = (Config_Ptr->Compare_output_Non_PWM>>1);
		TCCR1A_REG->bits.COM1B0_BIT = (Config_Ptr->Compare_output_Non_PWM>>0);
		OCR1AH_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		OCR1AL_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		OCR1BH_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		OCR1BL_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		break;
	case TIMER1_FAST_PWM_8bIT_MODE:
		TCCR1A_REG->bits.FOC1A_BIT = LOGIC_LOW;
		TCCR1A_REG->bits.FOC1B_BIT = LOGIC_LOW;
		TCCR1A_REG->bits.COM1A1_BIT = (Config_Ptr->Compare_output_Fast_PWM>>1);
		TCCR1A_REG->bits.COM1A0_BIT = (Config_Ptr->Compare_output_Fast_PWM>>0);
		TCCR1A_REG->bits.COM1B1_BIT = (Config_Ptr->Compare_output_Fast_PWM>>1);
		TCCR1A_REG->bits.COM1B0_BIT = (Config_Ptr->Compare_output_Fast_PWM>>0);
		OCR1AH_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		OCR1AL_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		OCR1BH_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		OCR1BL_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		break;
	case TIMER1_FAST_PWM_9bIT_MODE:
		TCCR1A_REG->bits.FOC1A_BIT = LOGIC_LOW;
		TCCR1A_REG->bits.FOC1B_BIT = LOGIC_LOW;
		TCCR1A_REG->bits.COM1A1_BIT = (Config_Ptr->Compare_output_Fast_PWM>>1);
		TCCR1A_REG->bits.COM1A0_BIT = (Config_Ptr->Compare_output_Fast_PWM>>0);
		TCCR1A_REG->bits.COM1B1_BIT = (Config_Ptr->Compare_output_Fast_PWM>>1);
		TCCR1A_REG->bits.COM1B0_BIT = (Config_Ptr->Compare_output_Fast_PWM>>0);
		OCR1AH_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		OCR1AL_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		OCR1BH_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		OCR1BL_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		break;
	case TIMER1_FAST_PWM_10bIT_MODE:
		TCCR1A_REG->bits.FOC1A_BIT = LOGIC_LOW;
		TCCR1A_REG->bits.FOC1B_BIT = LOGIC_LOW;
		TCCR1A_REG->bits.COM1A1_BIT = (Config_Ptr->Compare_output_Fast_PWM>>1);
		TCCR1A_REG->bits.COM1A0_BIT = (Config_Ptr->Compare_output_Fast_PWM>>0);
		TCCR1A_REG->bits.COM1B1_BIT = (Config_Ptr->Compare_output_Fast_PWM>>1);
		TCCR1A_REG->bits.COM1B0_BIT = (Config_Ptr->Compare_output_Fast_PWM>>0);
		OCR1AH_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		OCR1AL_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		OCR1BH_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		OCR1BL_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		break;
	case TIMER1_PHASE_FREQUENCY_CORRECT_PWM_ICR1_MODE:
		TCCR1A_REG->bits.FOC1A_BIT = LOGIC_LOW;
		TCCR1A_REG->bits.FOC1B_BIT = LOGIC_LOW;
		TCCR1A_REG->bits.COM1A1_BIT = (Config_Ptr->Compare_output_Phase_Correct_PWM>>1);
		TCCR1A_REG->bits.COM1A0_BIT = (Config_Ptr->Compare_output_Phase_Correct_PWM>>0);
		TCCR1A_REG->bits.COM1B1_BIT = (Config_Ptr->Compare_output_Phase_Correct_PWM>>1);
		TCCR1A_REG->bits.COM1B0_BIT = (Config_Ptr->Compare_output_Phase_Correct_PWM>>0);
		OCR1AH_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		OCR1AL_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		OCR1BH_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		OCR1BL_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		break;
	case TIMER1_PHASE_FREQUENCY_CORRECT_PWM_OCR1A_MODE:
		TCCR1A_REG->bits.FOC1A_BIT = LOGIC_LOW;
		TCCR1A_REG->bits.FOC1B_BIT = LOGIC_LOW;
		TCCR1A_REG->bits.COM1A1_BIT = (Config_Ptr->Compare_output_Phase_Correct_PWM>>1);
		TCCR1A_REG->bits.COM1A0_BIT = (Config_Ptr->Compare_output_Phase_Correct_PWM>>0);
		TCCR1A_REG->bits.COM1B1_BIT = (Config_Ptr->Compare_output_Phase_Correct_PWM>>1);
		TCCR1A_REG->bits.COM1B0_BIT = (Config_Ptr->Compare_output_Phase_Correct_PWM>>0);
		OCR1AH_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		OCR1AL_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		OCR1BH_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		OCR1BL_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		break;
	case TIMER1_PHASE_CORRECT_PWM_ICR1_MODE:
		TCCR1A_REG->bits.FOC1A_BIT = LOGIC_LOW;
		TCCR1A_REG->bits.FOC1B_BIT = LOGIC_LOW;
		TCCR1A_REG->bits.COM1A1_BIT = (Config_Ptr->Compare_output_Phase_Correct_PWM>>1);
		TCCR1A_REG->bits.COM1A0_BIT = (Config_Ptr->Compare_output_Phase_Correct_PWM>>0);
		TCCR1A_REG->bits.COM1B1_BIT = (Config_Ptr->Compare_output_Phase_Correct_PWM>>1);
		TCCR1A_REG->bits.COM1B0_BIT = (Config_Ptr->Compare_output_Phase_Correct_PWM>>0);
		OCR1AH_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		OCR1AL_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		OCR1BH_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		OCR1BL_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		break;
	case TIMER1_PHASE_CORRECT_PWM_OCR1A_MODE:
		TCCR1A_REG->bits.FOC1A_BIT = LOGIC_LOW;
		TCCR1A_REG->bits.FOC1B_BIT = LOGIC_LOW;
		TCCR1A_REG->bits.COM1A1_BIT = (Config_Ptr->Compare_output_Phase_Correct_PWM>>1);
		TCCR1A_REG->bits.COM1A0_BIT = (Config_Ptr->Compare_output_Phase_Correct_PWM>>0);
		TCCR1A_REG->bits.COM1B1_BIT = (Config_Ptr->Compare_output_Phase_Correct_PWM>>1);
		TCCR1A_REG->bits.COM1B0_BIT = (Config_Ptr->Compare_output_Phase_Correct_PWM>>0);
		OCR1AH_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		OCR1AL_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		OCR1BH_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		OCR1BL_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		break;
	case TIMER1_CTC_ICR1_MODE:
		TCCR1A_REG->bits.FOC1A_BIT = LOGIC_LOW;
		TCCR1A_REG->bits.FOC1B_BIT = LOGIC_LOW;
		TCCR1A_REG->bits.COM1A1_BIT = (Config_Ptr->Compare_output_Non_PWM>>1);
		TCCR1A_REG->bits.COM1A0_BIT = (Config_Ptr->Compare_output_Non_PWM>>0);
		TCCR1A_REG->bits.COM1B1_BIT = (Config_Ptr->Compare_output_Non_PWM>>1);
		TCCR1A_REG->bits.COM1B0_BIT = (Config_Ptr->Compare_output_Non_PWM>>0);
		OCR1AH_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		OCR1AL_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		OCR1BH_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		OCR1BL_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		break;
	case TIMER1_FAST_PWM_ICR1_MODE:
		TCCR1A_REG->bits.FOC1A_BIT = LOGIC_LOW;
		TCCR1A_REG->bits.FOC1B_BIT = LOGIC_LOW;
		TCCR1A_REG->bits.COM1A1_BIT = (Config_Ptr->Compare_output_Fast_PWM>>1);
		TCCR1A_REG->bits.COM1A0_BIT = (Config_Ptr->Compare_output_Fast_PWM>>0);
		TCCR1A_REG->bits.COM1B1_BIT = (Config_Ptr->Compare_output_Fast_PWM>>1);
		TCCR1A_REG->bits.COM1B0_BIT = (Config_Ptr->Compare_output_Fast_PWM>>0);
		OCR1AH_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		OCR1AL_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		OCR1BH_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		OCR1BL_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		break;
	case TIMER1_FAST_PWM_OCR1A_MODE:
		TCCR1A_REG->bits.FOC1A_BIT = LOGIC_LOW;
		TCCR1A_REG->bits.FOC1B_BIT = LOGIC_LOW;
		TCCR1A_REG->bits.COM1A1_BIT = (Config_Ptr->Compare_output_Fast_PWM>>1);
		TCCR1A_REG->bits.COM1A0_BIT = (Config_Ptr->Compare_output_Fast_PWM>>0);
		TCCR1A_REG->bits.COM1B1_BIT = (Config_Ptr->Compare_output_Fast_PWM>>1);
		TCCR1A_REG->bits.COM1B0_BIT = (Config_Ptr->Compare_output_Fast_PWM>>0);
		OCR1AH_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		OCR1AL_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		OCR1BH_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		OCR1BL_REG = Config_Ptr->TIMER1_COMPARE_VALUE;
		break;
	}
	TCNT1L = (Config_Ptr->TIMER1_INITIAL_VALUE);
	TCNT1H = (Config_Ptr->TIMER1_INITIAL_VALUE >> 8);
	TCCR1A_REG->bits.WGM10_BIT = (Config_Ptr->Mode);
	TCCR1A_REG->bits.WGM11_BIT = (Config_Ptr->Mode>> 1);
	TCCR1B_REG->bits.WGM12_BIT = (Config_Ptr->Mode >> 2);
	TCCR1B_REG->bits.WGM13_BIT = (Config_Ptr->Mode >> 3);
	//TCCR0_REG->FULL_REG = ((TCCR0_REG->FULL_REG & CLOCK_SELECT_MASK) | (Config_Ptr->Clock_Select));
}
void TIMER1_Start(const TIMER1_INIT_CONFIG* Config_Ptr)
{
	TCCR1B_REG->FULL_REG = ((TCCR1B_REG->FULL_REG & CLOCK_SELECT_MASK) | (Config_Ptr->Clock_Select));
}
void TIMER1_Stop(const TIMER1_INIT_CONFIG* Config_Ptr)
{
	TCCR1B_REG->FULL_REG = ((TCCR1B_REG->FULL_REG & CLOCK_SELECT_MASK) | (NO_CLOCK));
}
u16 TIMER1_GetCounts(void)
{
	u16 counts = 0;
	counts = TCNT1H_REG;
	counts <<= 8;
	counts |= TCNT1L_REG;
	return counts;
}
void TIMER1_SetDelayTimeMilliSec(const TIMER1_INIT_CONFIG* Config_Ptr, u32 copy_u32TimeMS)
{
	/* Assuming we are using 16MHz FCPU and Prescaler 1024  Tick time = 2 Micro seconds */
	switch(Config_Ptr->Mode)
	{
	case TIMER1_NORMAL_MODE:
		timer1OverFlowCounter = (((copy_u32TimeMS * 1000)/TICK_TIME) / TOP_VALUE);
		timer1RemCounter = (u16)(((copy_u32TimeMS * 1000)/TICK_TIME) % TOP_VALUE);
		TIMER1_IntEnable(Config_Ptr);
		TIMER1_Start(Config_Ptr);
		break;
	}
}
void TIMER1_IntEnable(const TIMER1_INIT_CONFIG* Config_Ptr)
{
	if(Config_Ptr->Mode == TIMER1_NORMAL_MODE)
	{
		TIMSK_REG->bits.TOIE1_BIT = LOGIC_HIGH;
	}
	/*else if (Config_Ptr->Mode == TIMER1_CTC_MODE)
	{
		TIMSK_REG->bits.OCIE0_BIT = LOGIC_HIGH;
	}
	else
	{
		//return error;
	}
	 */
}
void TIMER1_IntDisable(const TIMER1_INIT_CONFIG* Config_Ptr)
{
	if(Config_Ptr->Mode == TIMER1_NORMAL_MODE)
	{
		TIMSK_REG->bits.TOIE1_BIT = LOGIC_HIGH;
	}
	/*	else if (Config_Ptr->Mode == TIMER1_CTC_MODE)
	{
		TIMSK_REG->bits.OCIE0_BIT = LOGIC_LOW;
	}
	else
	{
		//return error;
	}
	 */
}

void TIMER1_SetCallBack(void(*ptrfn)(void))
{
	timer1PtrCallBack = ptrfn;
}
void TIMER1_SetFastPWM(const TIMER1_INIT_CONFIG* Config_Ptr, u16 duty)
{
	/* pwm freq = FCPU/(prescaler*256) */

	/* duty cycle */
	u16 dutyval = 0;
	dutyval = (u16)(((u32)duty*TOP_VALUE)/100);

	OCR1AL_REG = dutyval;
	OCR1AH_REG = (dutyval >> 8);

	OCR1BL_REG = dutyval;
	OCR1BH_REG = (dutyval >> 8);

}
void TIMER1_SetPhaseCorrectPWM(const TIMER1_INIT_CONFIG* Config_Ptr, u16 duty);

void TIMER1_GetEventDuration(void)
{
	ICR1L_REG = 0;
	ICR1H_REG = 0;
	TIMSK_REG->bits.TICIE1_BIT = LOGIC_HIGH;
	TCCR1B_REG->bits.ICNC1_BIT = LOGIC_LOW;
	TCCR1B_REG->bits.ICES1_BIT = RISING_EDGE;
}
void TIMER1_GetSignalFrequency(void)
{
	ICR1L_REG = 0;
	ICR1H_REG = 0;
	TIMSK_REG->bits.TICIE1_BIT = LOGIC_HIGH;
	TCCR1B_REG->bits.ICNC1_BIT = LOGIC_LOW;
	TCCR1B_REG->bits.ICES1_BIT = RISING_EDGE;
}
void TIMER1_GetSignalDutyCycle(void)
{
	ICR1L_REG = 0;
	ICR1H_REG = 0;
	TIMSK_REG->bits.TICIE1_BIT = LOGIC_HIGH;
	TCCR1B_REG->bits.ICNC1_BIT = LOGIC_LOW;
	TCCR1B_REG->bits.ICES1_BIT = RISING_EDGE;
}

u16 TIMER1_GetInputCaptureValue(void)
{
	u16 counts = 0;
	counts = ICR1H_REG;
	counts <<= 8;
	counts |= ICR1L_REG;
	return counts;
}

void TIMER1_SetInputCaptureEdgeDetection(u8 trigger)
{
	TCCR1B_REG->bits.ICES1_BIT = trigger;
}

void TIMER1_ClearTimerValue(void)
{
	TCNT1H_REG = 0;
	TCNT1L_REG = 0;
}

ISR(TIMER1_OVF_vect)
{
	/* For the delay func */
	/*
	overFlowCounter--;

	if(overFlowCounter == 0)
	{
		TCNT1L_REG = (TOP_VALUE - remCounter);
		TCNT1H_REG = ((TOP_VALUE - remCounter) >> 8);
	}
	if((ptrCallBack != NULL_PTR) && (overFlowCounter == -1))
	{
		(*ptrCallBack)();
	}
	 */

	if((timer1PtrCallBack != NULL_PTR) && (timer1OverFlowCounter == -1))
	{
		(*timer1PtrCallBack)();
	}
}

ISR(TIMER1_CAPT_vect)
{
	if(timer1PtrCallBack != NULL_PTR)
	{
		(*timer1PtrCallBack)();
	}
}

ISR(TIMER1_COMPA_vect)
{
	if(timer1PtrCallBack != NULL_PTR)
	{
		(*timer1PtrCallBack)();
	}
}


ISR(TIMER1_COMPB_vect)
{
	if(timer1PtrCallBack != NULL_PTR)
	{
		(*timer1PtrCallBack)();
	}
}
