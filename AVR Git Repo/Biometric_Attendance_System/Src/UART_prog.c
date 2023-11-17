/*
 * UART_prog.c
 *
 *  Created on: Oct 29, 2023
 *      Author: Ebram Habib
 */

#include "std_types.h"
#include "UART_int.h"
#include "UART_config.h"
#include "UART_priv.h"
#include <avr/interrupt.h>


/*******************************************************************************
 *                      Global Variables	                                   *
 *******************************************************************************/
static void(*ptrCallBack)(u8) = NULL_PTR;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(void)
{
	u8 regVal = 0;
	u16 ubrr_value = 0;

	/* U2X = 1 for double transmission speed */
	UCSRA_REG = (UART_TRANSMISSION_SPEED<<U2X_BIT);

	/************************** UCSRB Description **************************
	 * RXCIE = 0 disable USART RX Complete Interrupt Enable
	 * TXCIE = 0 disable USART Tx Complete Interrupt Enable
	 * UDRIE = 0 disable USART Data Register Empty Interrupt Enable
	 * RXEN  = 1 Receiver Enable
	 * RXEN  = 1 Transmitter Enable
	 * UCSZ2 = 5:9 bits data modes
	 * RXB8 & TXB8 not used for 8-bit data mode
	 ***********************************************************************/
	regVal = 0;
	regVal = (1<<RXEN_BIT) | (1<<TXEN_BIT) | ((UART_BitData>>2)<<UCSZ2_BIT);
	UCSRB_REG = regVal;
	/************************** UCSRC Description **************************
	 * URSEL   = 1 The URSEL must be one when writing the UCSRC
	 * UMSEL   = 0 Asynchronous Operation
	 * UPM1:0  = parity bit
	 * USBS    = stop bit
	 * UCSZ1:0 = 5:9 bits data modes
	 * UCPOL   = 0 Used with the Synchronous operation only
	 ***********************************************************************/
	regVal = 0;
	regVal= (1 <<URSEL_BIT) | (((UART_BitData & 0x02)>>1)<<UCSZ1_BIT) | ((UART_BitData & 0x01)<<UCSZ0_BIT) | ((UART_Parity & 0x01)<<UPM0_BIT) | ((UART_Parity & 0x02)<<UPM1_BIT) | ((UART_StopBit)<<USBS_BIT);
	UCSRC_REG = regVal;

	/* Calculate the UBRR register value */
	ubrr_value = (u16)(((F_CPU / (UART_BaudRate * 8UL))) - 1);

	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
	UBRRH_REG = ubrr_value>>8;
	UBRRL_REG = ubrr_value;

}

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const u8 data)
{
	/*
	 * UDRE flag is set when the Tx buffer (UDR) is empty and ready for
	 * transmitting a new byte so wait until this flag is set to one
	 */
	while(!(UCSRA_REG & (1<<UDRE_BIT)));

	/*
	 * Put the required data in the UDR register and it also clear the UDRE flag as
	 * the UDR register is not empty now
	 */
	UDR_REG = data;
}

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
void UART_recieveByteSynchNonBlocking(u8* data)
{
	/* RXC flag is set when the UART receive data so wait until this flag is set to one */
	while(!(UCSRA_REG & (1<<RXC_BIT)));

	/*
	 * Read the received data from the Rx buffer (UDR)
	 * The RXC flag will be cleared after read the data
	 */
	*data = UDR_REG;
}

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const u8 *Str)
{

	/* Sending the whole string one character after the other till we find the null character */
	while(*Str != '\0')
	{
		UART_sendByte(*Str);
		Str++;
	}
}

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveStringAsynchCallBack(void(*ptrfn)(u8)) // Receive until #

{
	ptrCallBack = ptrfn;
	UCSRB_REG |= (1<<RXCIE_BIT);
}

void UART_receiveByteAsynchCallBack(void(*ptrfn)(u8))
{
	ptrCallBack = ptrfn;
	UCSRB_REG |= (1<<RXCIE_BIT);
}

ISR(USART_RXC_vect)
{
	static u8 byte = 0;

	byte = UDR_REG;

	if((*ptrCallBack) != NULL_PTR)
	{
		(*ptrCallBack)(byte);
	}
}
