/*
 * main.c
 *
 *  Created on: Oct 29, 2023
 *      Author: Ebram Habib
 */

#include "std_types.h"
#include "UART_int.h"
#include "GIE_int.h"

int main()
{

	u8 Str[20];
	u8 data = 0;

	/* Initialize the UART driver with Baud-rate = 9600 bits/sec */
	UART_init();

	while(1)
	{
		UART_recieveByte(&data); /* Receive Byte from Terminal */
		UART_sendByte(data);       /* Re-send the received byte to Terminal */
		//		UART_receiveString(Str);     /* Receive String from Terminal */
		//	    UART_sendString(Str);        /* Re-send the string to Terminal */
	}
}

