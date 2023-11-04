/*
 * TWI_priv.h
 *
 *  Created on: Oct 31, 2023
 *      Author: Ebram Habib
 */

#ifndef TWI_PRIV_H_
#define TWI_PRIV_H_


/* TWSR Register Pins  */
#define TWPS0   0
#define TWPS1   1
#define TWS3    3
#define TWS4    4
#define TWS5    5
#define TWS6    6
#define TWS7    7

/* TWAR Register Pins  */
#define TWGCE   0
#define TWA0    1
#define TWA1    2
#define TWA2    3
#define TWA3    4
#define TWA4    5
#define TWA5    6
#define TWA6    7

/* TWCR Register Pins  */
#define TWIE    0
#define TWEN    2
#define TWWC    3
#define TWSTO   4
#define TWSTA   5
#define TWEA    6
#define TWINT   7

/* Mask to read the error status from the status register */
#define TWI_ERROR_STATUS_MASK 0xF8

#define TWCR_REG *((volatile u8*) 0x56)
#define TWDR_REG *((volatile u8*) 0x23)
#define TWAR_REG *((volatile u8*) 0x22)
#define TWSR_REG *((volatile u8*) 0x21)
#define TWBR_REG *((volatile u8*) 0x20)

#endif /* TWI_PRIV_H_ */
