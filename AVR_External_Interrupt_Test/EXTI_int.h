/*
 * EXTI_int.h
 *
 *  Created on: Oct 22, 2023
 *      Author: Ebram Habib
 */

#ifndef EXTI_INT_H_
#define EXTI_INT_H_

#include "std_types.h"

#define EXTI_INT0_ID 6
#define EXTI_INT1_ID 7
#define EXTI_INT2_ID 5
#define	LOW_LEVEL 0
#define	ANY_CHANGE 1
#define	FALLING_EDGE 2
#define	RISING_EDGE 3

void EXTI_voidEnable(u8 copy_u8IntID, u8 trigger);
void EXTI_voidDisable(u8 copy_u8IntID);
void EXTI_voidSetCallBack(void(*ptrfn)(void),u8 copy_u8IntID);
void __vector_1(void)__attribute__((signal));
void __vector_2(void)__attribute__((signal));
void __vector_3(void)__attribute__((signal));

#endif /* EXTI_INT_H_ */
