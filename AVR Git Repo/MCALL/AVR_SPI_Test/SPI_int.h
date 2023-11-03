/*
 * SPI_int.h
 *
 *  Created on: Oct 30, 2023
 *      Author: Ebram Habib
 */

#ifndef SPI_INT_H_
#define SPI_INT_H_

#include "SPI_config.h"

void SPI_init(const SPI_INIT_CONFIG* Config_Ptr);
void SPI_intEnable(void);
void SPI_disable(void);
void SPI_transferSynchBlocking(u8 send, u8* receive);
void SPI_transferAsynchCallBack(u8 send);
void SPI_SetCallBack(void(*ptrfn)(u8));

#endif /* SPI_INT_H_ */
