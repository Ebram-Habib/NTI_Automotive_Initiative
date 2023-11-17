/*
 * UART_config.h
 *
 *  Created on: Oct 29, 2023
 *      Author: Ebram Habib
 */

#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/


/* choosing the mode of UART */

#define ASYNCHRONOUS_OPERATION	0
#define SYNCHRONOUS_OPERATION	1

#define UART_MODE_SELECT	ASYNCHRONOUS_OPERATION

/* choosing the number of bits being sent as data in each frame */

#define FIVE_BITS	0
#define SIX_BITS	1
#define SEVEN_BITS	2
#define EIGHT_BITS	3
#define NINE_BITS	7

#define UART_BitData	EIGHT_BITS

/* choosing the status of the parity bit */

#define NO_PARITY	0
#define EVEN_PARITY	2
#define ODD_PARITY	3

#define UART_Parity		NO_PARITY

/* choosing the number of stop bits in each frame */

#define ONE_STOP_BIT	0
#define TWO_STOP_BITS	1

#define UART_StopBit	ONE_STOP_BIT

/* choosing the transmission speed */

#define NORMAL_SPEED	0
#define DOUBLE_SPEED	1

#define UART_TRANSMISSION_SPEED	DOUBLE_SPEED

/* choosing the baud rate used by the device */

#define BAUDRATE_9600	9600
#define BAUDRATE_14400	14400
#define BAUDRATE_19200	19200
#define BAUDRATE_38400	38400
#define BAUDRATE_57600	57600
#define BAUDRATE_115200	115200
#define BAUDRATE_128000	128000
#define BAUDRATE_256000	256000

#define UART_BaudRate	BAUDRATE_57600

#endif /* UART_CONFIG_H_ */
