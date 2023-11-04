/*
 * RTC_priv.h
 *
 *  Created on: Nov 3, 2023
 *      Author: Ebram Habib
 */

#ifndef RTC_PRIV_H_
#define RTC_PRIV_H_

#include "std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define ERROR 0
#define SUCCESS 1

#define RTC_SLAVE_ADDRESS 			0xD0
#define RTC_POINTER_TIME_ADDRESS	0X00
#define RTC_POINTER_DATE_ADDRESS	0X03
#define WRITE						0x00
#define READ						0x01


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

static u8 RTC_decimalToBCD(u8 val);
static u8 RTC_BCDdecimal(u8 val);

#endif /* RTC_PRIV_H_ */
