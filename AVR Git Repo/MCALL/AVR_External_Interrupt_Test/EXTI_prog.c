/*
 * EXTI_prog.c
 *
 *  Created on: Oct 22, 2023
 *      Author: Ebram Habib
 */

#include "std_types.h"
#include "EXTI_int.h"
#include "EXTI_priv.h"
#include <avr/interrupt.h>

void (*ptrCallBack[])(void) = {NULL_PTR,NULL_PTR,NULL_PTR};

void EXTI_voidEnable(u8 copy_u8IntID, u8 trigger)
{
	GICR |= (1<<copy_u8IntID);

	switch(copy_u8IntID)
	{
	case EXTI_INT0_ID:
		MCUCR &= 0b11111100;
		MCUCR |= trigger;
		break;
	case EXTI_INT1_ID:
		MCUCR &= 0b11110011;
		MCUCR |= (trigger<<2);
		break;
	case EXTI_INT2_ID:
		if(trigger-2 >= 0)
		{
			MCUCR &= 0b10111111;
			MCUCSR |= ((trigger-2)<<6);
		}
		break;
	}

}

void EXTI_voidDisable(u8 copy_u8IntID)
{
	GICR &= ~(1<<copy_u8IntID);
}

void EXTI_voidSetCallBack(void(*ptrfn)(void),u8 copy_u8IntID)
{
	switch (copy_u8IntID)
	{
		case EXTI_INT0_ID:
			ptrCallBack[0] = ptrfn;
			break;
		case EXTI_INT1_ID:
					ptrCallBack[1] = ptrfn;
					break;
		case EXTI_INT2_ID:
					ptrCallBack[2] = ptrfn;
					break;
	}
}

ISR(INT0_vect)
{
	if((*ptrCallBack[0]) != NULL_PTR)
	{
		(*ptrCallBack[0])();
	}
}
ISR(INT1_vect)
{
	if((*ptrCallBack[1]) != NULL_PTR)
	{
		(*ptrCallBack[1])();
	}
}
ISR(INT2_vect)
{
	if((*ptrCallBack[2]) != NULL_PTR)
	{
		(*ptrCallBack[2])();
	}
}


/* void __vector_1(void)
{
	if((*ptrCallBack[0]) != NULL_PTR)
	{
		(*ptrCallBack[0])();
	}
}
void __vector_2(void)
{
	if((*ptrCallBack[1]) != NULL_PTR)
	{
		(*ptrCallBack[1])();
	}
}
void __vector_3(void)
{
	if((*ptrCallBack[2]) != NULL_PTR)
	{
		(*ptrCallBack[2])();
	}
}

*/
