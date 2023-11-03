/*
 * main.c
 *
 *  Created on: Oct 31, 2023
 *      Author: Ebram Habib
 */

#include "std_types.h"
#include "TWI_int.h"
#include "EEPROM_int.h"
#include "GIE_int.h"
#include "GPIO_Int.h"
#include <avr/delay.h>


int main()
{

	u8 val = 0;

		DIO_voidSetPinDirection(pPORTD, Pin0, output);
		DIO_voidSetPinDirection(pPORTD, pin1, output);
		DIO_voidSetPinDirection(pPORTD, pin2, output);
		DIO_voidSetPinDirection(pPORTD, pin3, output);
		DIO_voidSetPinDirection(pPORTD, pin4, output);
		DIO_voidSetPinDirection(pPORTD, pin5, output);
		DIO_voidSetPinDirection(pPORTD, pin6, output);
		DIO_voidSetPinDirection(pPORTD, pin7, output);

		EEPROM_init();

		EEPROM_writeByte(0x0311, 0x11); /* Write 0x0F in the external EEPROM */
		_delay_ms(10);
		EEPROM_readByte(0x0311, &val);  /* Read 0x0F from the external EEPROM */
		_delay_ms(10);

		if(val == 0x11)
		{
			DIO_voidSetPinValue(pPORTD, pin3, LOGIC_HIGH);
		}
		else
		{
			DIO_voidSetPinValue(pPORTD, Pin0, LOGIC_HIGH);
			DIO_voidSetPinValue(pPORTD, pin7, LOGIC_HIGH);
		}
		while(1)
		{


		}
}
