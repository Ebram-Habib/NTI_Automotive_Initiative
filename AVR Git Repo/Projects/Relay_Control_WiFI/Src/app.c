/*
 * main.c
 *
 *  Created on: Nov 17, 2023
 *      Author: Ebram Habib
 */


#include "std_types.h"
#include "UART_int.h"
#include "GPIO_Int.h"
#include "GIE_int.h"
#include "WiFi_int.h"

int main()
{
	/* create a variable to hold the received byte from UART */
	u8 byte=0;

	/* Initialize the pin used for the relay */
	DIO_voidSetPinDirection(pPORTA, pin7, output);
	DIO_voidSetPinValue(pPORTA, pin7, LOGIC_LOW);

	/* Enable global interrupt to be used with the timer for delays */
	GIE_Enable();
	/* Initialize the Wi-Fi module and set it to work as both AP+Station */
	WIFI_init();
	/* Connect ESP module to the network */
	WIFI_connectRouter();
	/* Short delay to process the request */
	WIFI_delayMilliSec(1);
	/* Connect ESP module to the phone */
	WIFI_connectPhone();

	while(1)
	{
		/* Keep reading bytes from the ESP module whenever sent */
		WIFI_receiveData(&byte);
		/* If we receive the 'N' Letter we turn activate the relay */
		if(byte == 'N')
		{
			DIO_voidSetPinValue(pPORTA, pin7, LOGIC_HIGH);
		}
		/* If we receive the 'F' Letter we turn deactivate the relay */
		else if(byte == 'F')
		{
			DIO_voidSetPinValue(pPORTA, pin7, LOGIC_LOW);
		}

	}
}

