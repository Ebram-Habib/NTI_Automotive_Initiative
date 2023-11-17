/*
 * FingerPS_int.h
 *
 *  Created on: Nov 4, 2023
 *      Author: Ebram Habib
 */

#ifndef FINGERPS_INT_H_
#define FINGERPS_INT_H_

/*  Macros  */
#define SUCCESS		1
#define ERROR		0
#define CHARACTERFILE1	1
#define CHARACTERFILE2	2


/*  Prototypes  */

void FingerPS_init(void);
u8 FingerPS_handShake(void);
u8 FingerPS_genImg(void);
u8 FingerPS_convertImg2CharFile(u8 buffID);
u8 FingerPS_genTemplate(void);
u8 FingerPS_strTemplate(u8 ID);
u8 FingerPS_searchFinger(void); /* used with enrollment mode ---  1:n must be done at each enrollment to ensure that the template doesn't already exist */
u8 FingerPS_emptyLibrary(void);
u8 FingerPS_deleteFinger(void);
u8 FingerPS_LoadCharFile(void);
static u16 FingerPS_calcCheckSum(u8* frame);
u8 FingerPS_match(void); /* used with attendance mode */
u8 FingerPS_AuraNormal(void);
u8 FingerPS_AuraSuccess(void);
u8 FingerPS_AuraError(void);
/* Functions to use the delay with Timer0 */
void delayCallBack(void);
void delayMilliSec(u32 millisec);

/* UART Call Back Function */
void getByte(u8 byte);

#endif /* FINGERPS_INT_H_ */
