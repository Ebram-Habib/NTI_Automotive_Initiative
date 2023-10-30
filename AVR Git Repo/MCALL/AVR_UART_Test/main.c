/*
 * main.c
 *
 *  Created on: Oct 29, 2023
 *      Author: Ebram Habib
 */

#include "std_types.h"
#include "UART_int.h"
#include "GIE_int.h"

u8 Str[20]="hellow testing...";
u8 data = 0;

void getbyte(u8 byte);

int main()
{
	GIE_Enable();

	/* Initialize the UART driver with Baud-rate = 9600 bits/sec */
	UART_init();
	UART_receiveByteAsynchCallBack(getbyte); /* Receive Byte from Terminal */
	while(1)
	{
		if(data != 0)
		{
			UART_sendByte(data);
			data = 0;/* Re-send the received byte to Terminal */
		}
		//				UART_receiveString(Str);     /* Receive String from Terminal */
		//			    UART_sendString(Str);        /* Re-send the string to Terminal */
	}
}

void getbyte(u8 byte)
{
	data = byte;
}
