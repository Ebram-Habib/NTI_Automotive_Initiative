/*
 * main.c
 *
 *  Created on: Oct 29, 2023
 *      Author: Ebram Habib
 */

#include "std_types.h"
#include "UART_int.h"
#include "GIE_int.h"
#include "LCD_int.h"
#if 1					/* receive code */

u8 Str2[20]={0};
u8 data = 0;
u8 stringReceived = 0;

void getbyte(u8 byte);
void getstring(u8 byte);
int main()
{
	u8 flag = 0;

	/* Initialize the UART driver with Baud-rate = 9600 bits/sec */
	UART_init();
	UART_receiveStringAsynchCallBack(getstring); // Receive until #
	//	UART_receiveByteAsynchCallBack(getbyte);
	//	UART_recieveByteSynchNonBlocking(&data);/* Receive Byte from Terminal */
	GIE_Enable();
	flag = 1;

	while(1)
	{

		if(stringReceived == 1 && flag == 1)
		{
			//			UART_sendByte(data);
			UART_sendString(Str2);
			flag = 0;
			stringReceived = 0;
		}
	}
}

void getbyte(u8 byte)
{
	data = byte;
	stringReceived = 1;
}
void getstring(u8 byte)
{
	static u8 i=0;

	if(stringReceived == 0)
	{
		if(byte == '#')
		{
			Str2[i] = '\0';
			stringReceived = 1;
		}
		else
		{
			Str2[i] = byte;
			i++;
		}

	}
}
#endif
#if 0   /* send code */

u8 Str1[20]="Hello world from MC1#";
u8 data = 0;

int main()
{

	/* Initialize the UART driver with Baud-rate = 9600 bits/sec */
	UART_init();
	UART_sendString(Str1);
	while(1)
	{


	}

}


#endif
