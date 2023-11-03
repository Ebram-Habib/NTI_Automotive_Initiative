/*
 * main.c
 *
 *  Created on: Oct 30, 2023
 *      Author: Ebram Habib
 */
#include "std_types.h"
#include "common_macros.h"
#include "SPI_int.h"
#include "GIE_int.h"
#include "GPIO_Int.h"
#include "avr/delay.h"

u8 dataSent = 0;
u8 dataReceived = 0;


SPI_INIT_CONFIG config = {
		SPI_MSB_FIRST,
		SPI_MASTER,
		SPI_IDLE_LOW,
		SPI_SAMPLE_FIRST,
		SPI_NORMAL_SPEED_MODE,
		SPI_NORMAL_SPEED_FCPU_DIVIDED_BY_16
};

int main()
{
	DIO_voidSetPinDirection(pPORTB, pin4, output);
	DIO_voidSetPinDirection(pPORTB, pin5, output);
	DIO_voidSetPinDirection(pPORTB, pin6, input);
	DIO_voidSetPinDirection(pPORTB, pin7, output);
	SPI_init(&config);

	while(1)
	{
		SPI_transferSynchBlocking(0x01, &dataReceived);
		_delay_ms(100);
		SPI_transferSynchBlocking(0x02, &dataReceived);
		_delay_ms(100);
		SPI_transferSynchBlocking(0x03, &dataReceived);
		_delay_ms(100);

	}

}
