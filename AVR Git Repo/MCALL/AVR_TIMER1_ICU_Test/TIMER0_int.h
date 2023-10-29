/*
 * TIMER0_int.h
 *
 *  Created on: Oct 27, 2023
 *      Author: Ebram Habib
 */

#ifndef TIMER0_INT_H_
#define TIMER0_INT_H_

#include "TIMER0_config.h"

void TIMER0_Init(const TIMER0_INIT_CONFIG* Config_Ptr);
void TIMER0_Start(const TIMER0_INIT_CONFIG* Config_Ptr);
void TIMER0_Stop(const TIMER0_INIT_CONFIG* Config_Ptr);
u8 TIMER0_GetCounts(void);
void TIMER0_SetDelayTimeMilliSec(const TIMER0_INIT_CONFIG* Config_Ptr, u32 copy_u32TimeMS);
void TIMER0_IntEnable(const TIMER0_INIT_CONFIG* Config_Ptr);
void TIMER0_IntDisable(const TIMER0_INIT_CONFIG* Config_Ptr);
void TIMER0_SetCallBack(void(*ptrfn)(void));
void TIMER0_SetFastPWM(const TIMER0_INIT_CONFIG* Config_Ptr, u8 duty);
void TIMER0_SetPhaseCorrectPWM(const TIMER0_INIT_CONFIG* Config_Ptr, u8 duty);

#endif /* TIMER0_INT_H_ */
