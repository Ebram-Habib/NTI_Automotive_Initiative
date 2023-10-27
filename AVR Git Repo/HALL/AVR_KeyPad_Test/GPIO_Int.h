/*
 * GPIO_Int.h
 *
 *  Created on: Oct 20, 2023
 *      Author: Ebram Habib
 */

#ifndef GPIO_INT_H_
#define GPIO_INT_H_

#include "std_types.h"
#include "GPIO_Cfg.h"

//#define pPORTA  *(volatile port*)0x30;
//#define pPORTB  *((volatile port*)0x33);
//#define pPORTC  *((volatile port*)0x36);
//#define pPORTD  *((volatile port*)0x39);

void DIO_voidSetPinDirection(port* Ptr_PortId, u8 Copy_u8PinId, u8 Copy_u8Direction);
void DIO_voidSetPinValue(port* Ptr_PortId, u8 Copy_u8PinId, u8 Copy_u8Value);
u8 DIO_voidGetPinValue(port* Ptr_PortId, u8 Copy_u8PinId);

void DIO_voidSetPortDirection(port* Ptr_PortId, u8 Copy_u8Direction);
void DIO_voidSetPortValue(port* Ptr_PortId, u8 Copy_u8Value);
u8 DIO_voidGetPortValue(port* Ptr_PortId);

#endif /* GPIO_INT_H_ */
