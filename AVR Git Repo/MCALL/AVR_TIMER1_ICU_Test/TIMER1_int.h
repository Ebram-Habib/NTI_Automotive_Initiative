/*
 * TIMER1_int.h
 *
 *  Created on: Oct 28, 2023
 *      Author: Ebram Habib
 */

#ifndef TIMER1_INT_H_
#define TIMER1_INT_H_

#include "TIMER1_config.h"

#define RISING_EDGE			1
#define FALLING_EDGE		0

void TIMER1_Init(const TIMER1_INIT_CONFIG* Config_Ptr);
void TIMER1_Start(const TIMER1_INIT_CONFIG* Config_Ptr);
void TIMER1_Stop(const TIMER1_INIT_CONFIG* Config_Ptr);
u16 TIMER1_GetCounts(void);
void TIMER1_SetDelayTimeMilliSec(const TIMER1_INIT_CONFIG* Config_Ptr, u32 copy_u32TimeMS);
void TIMER1_IntEnable(const TIMER1_INIT_CONFIG* Config_Ptr);
void TIMER1_IntDisable(const TIMER1_INIT_CONFIG* Config_Ptr);
void TIMER1_SetCallBack(void(*ptrfn)(void));
void TIMER1_SetFastPWM(const TIMER1_INIT_CONFIG* Config_Ptr, u16 duty);
void TIMER1_SetPhaseCorrectPWM(const TIMER1_INIT_CONFIG* Config_Ptr, u16 duty);
void TIMER1_GetEventDuration(void);
void TIMER1_GetSignalFrequency(void);
void TIMER1_GetSignalDutyCycle(void);
void TIMER1_ClearTimerValue(void);
void TIMER1_SetInputCaptureEdgeDetection(u8 trigger);
u16 TIMER1_GetInputCaptureValue(void);


#endif /* TIMER1_INT_H_ */
