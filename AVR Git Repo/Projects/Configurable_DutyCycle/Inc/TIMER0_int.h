/*
 * TIMER0_int.h
 *
 *  Created on: Oct 27, 2023
 *      Author: Ebram Habib
 */

#ifndef TIMER0_INT_H_
#define TIMER0_INT_H_

#include "TIMER0_config.h"

void Timer0_Init(const TIMER0_INIT_CONFIG* Config_Ptr);
void Timer0_Start(const TIMER0_INIT_CONFIG* Config_Ptr);
void Timer0_Stop(const TIMER0_INIT_CONFIG* Config_Ptr);
u8 Timer0_GetCounts(void);
void Timer0_SetDelayTimeMilliSec(const TIMER0_INIT_CONFIG* Config_Ptr, u32 copy_u32TimeMS);
void Timer0_IntEnable(const TIMER0_INIT_CONFIG* Config_Ptr);
void Timer0_IntDisable(const TIMER0_INIT_CONFIG* Config_Ptr);
void Timer0_SetCallBack(void(*ptrfn)(void));
void Timer0_SetFastPWM(const TIMER0_INIT_CONFIG* Config_Ptr, u8 duty);
void Timer0_SetPhaseCorrectPWM(const TIMER0_INIT_CONFIG* Config_Ptr, u8 duty);

#endif /* TIMER0_INT_H_ */
