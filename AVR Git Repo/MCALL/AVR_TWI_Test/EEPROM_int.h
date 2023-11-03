/*
 * EEPROM_int.h
 *
 *  Created on: Nov 1, 2023
 *      Author: Ebram Habib
 */

#ifndef EEPROM_INT_H_
#define EEPROM_INT_H_

#include "std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define ERROR 0
#define SUCCESS 1

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void EEPROM_init(void);
u8 EEPROM_writeByte(u16 u16addr,u8 u8data);
u8 EEPROM_readByte(u16 u16addr,u8 *u8data);


#endif /* EEPROM_INT_H_ */
