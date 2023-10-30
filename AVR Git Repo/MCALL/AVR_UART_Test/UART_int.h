/*
 * UART_int.h
 *
 *  Created on: Oct 29, 2023
 *      Author: Ebram Habib
 */

#ifndef UART_INT_H_
#define UART_INT_H_

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
void UART_init(void);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const u8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
void UART_recieveByteSynchNonBlocking(u8* data);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const u8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(u8 *Str); // Receive until #

/*
 * Description :
 * Receiving a byte using interrupt instead of polling.
 */
void UART_receiveByteAsynchCallBack(void(*ptrfn)(u8));

#endif /* UART_INT_H_ */
