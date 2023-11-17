/*
 * GPIO_Int.c
 *
 *  Created on: Oct 20, 2023
 *      Author: Ebram Habib
 */
#include "GPIO_Cfg.h"
#include "GPIO_Int.h"


port* const pPORTA = (port*) 0x39;
port* const pPORTB = (port*) 0x36;
port* const pPORTC = (port*) 0x33;
port* const pPORTD = (port*) 0x30;

void DIO_voidSetPinDirection(port* Ptr_PortId,u8 PIN_ID,u8 DIRECTION)
{
	switch(PIN_ID)
	{
	case pin0:
		Ptr_PortId->DDR_reg.bits.bit0 = DIRECTION;
		break;
	case pin1:
		Ptr_PortId->DDR_reg.bits.bit1 = DIRECTION;
		break;
	case pin2:
		Ptr_PortId->DDR_reg.bits.bit2 = DIRECTION;
		break;
	case pin3:
		Ptr_PortId->DDR_reg.bits.bit3 = DIRECTION;
		break;
	case pin4:
		Ptr_PortId->DDR_reg.bits.bit4 = DIRECTION;
		break;
	case pin5:
		Ptr_PortId->DDR_reg.bits.bit5 = DIRECTION;
		break;
	case pin6:
		Ptr_PortId->DDR_reg.bits.bit6 = DIRECTION;
		break;
	case pin7:
		Ptr_PortId->DDR_reg.bits.bit7 = DIRECTION;
		break;
	}
}

void DIO_voidSetPinValue(port* Ptr_PortId, u8 PIN_ID, u8 PIN_VAL)
{
	switch(PIN_ID)
	{
	case pin0:
		Ptr_PortId->PORT_reg.bits.bit0 = PIN_VAL;
		break;
	case pin1:
		Ptr_PortId->PORT_reg.bits.bit1 = PIN_VAL;
		break;
	case pin2:
		Ptr_PortId->PORT_reg.bits.bit2 = PIN_VAL;
		break;
	case pin3:
		Ptr_PortId->PORT_reg.bits.bit3 = PIN_VAL;
		break;
	case pin4:
		Ptr_PortId->PORT_reg.bits.bit4 = PIN_VAL;
		break;
	case pin5:
		Ptr_PortId->PORT_reg.bits.bit5 = PIN_VAL;
		break;
	case pin6:
		Ptr_PortId->PORT_reg.bits.bit6 = PIN_VAL;
		break;
	case pin7:
		Ptr_PortId->PORT_reg.bits.bit7 = PIN_VAL;
		break;
	}
}

u8 DIO_voidGetPinValue(port* Ptr_PortId, u8 PIN_ID)
{
	u8 u8PinValue;

	switch(PIN_ID)
	{
	case pin0:
		u8PinValue = Ptr_PortId->PIN_reg.bits.bit0;
		break;
	case pin1:
		u8PinValue = Ptr_PortId->PIN_reg.bits.bit1;
		break;
	case pin2:
		u8PinValue = Ptr_PortId->PIN_reg.bits.bit2;
		break;
	case pin3:
		u8PinValue = Ptr_PortId->PIN_reg.bits.bit3;
		break;
	case pin4:
		u8PinValue = Ptr_PortId->PIN_reg.bits.bit4;
		break;
	case pin5:
		u8PinValue = Ptr_PortId->PIN_reg.bits.bit5;
		break;
	case pin6:
		u8PinValue = Ptr_PortId->PIN_reg.bits.bit6;
		break;
	case pin7:
		u8PinValue = Ptr_PortId->PIN_reg.bits.bit7;
		break;
	}

	return u8PinValue;
}

void DIO_voidSetPortDirection(port* Ptr_PortId, u8 Copy_u8Direction)
{
	Ptr_PortId->DDR_reg.Full_Reg = Copy_u8Direction;
}

void DIO_voidSetPortValue(port* Ptr_PortId, u8 Copy_u8Value)
{
	Ptr_PortId->PORT_reg.Full_Reg = Copy_u8Value;
}

u8 DIO_voidGetPortValue(port* Ptr_PortId)
{
	return Ptr_PortId->PIN_reg.Full_Reg;
}
