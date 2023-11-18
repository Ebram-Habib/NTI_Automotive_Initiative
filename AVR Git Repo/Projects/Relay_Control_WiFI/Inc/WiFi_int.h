/*
 * WiFi_int.h
 *
 *  Created on: Nov 16, 2023
 *      Author: Ebram Habib
 */

#ifndef WIFI_INT_H_
#define WIFI_INT_H_


/* Function prototypes */

u8 WIFI_init(void);
u8 WIFI_connectRouter(void);
u8 WIFI_connectPhone(void);
u8 WIFI_receiveData(u8* data);
void WIFI_delayMilliSec(u32 millisec);
void WIFI_getByte(u8 byte);

#endif /* WIFI_INT_H_ */
