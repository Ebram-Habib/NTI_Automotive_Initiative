/*
 * TWI_int.h
 *
 *  Created on: Oct 31, 2023
 *      Author: Ebram Habib
 */

#ifndef TWI_INT_H_
#define TWI_INT_H_

#include "std_types.h"
#include "TWI_config.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* I2C Status Bits in the TWSR Register (Master Transmitter) */
#define TWI_MT_START         	 0x08 /* start has been sent */
#define TWI_MT_REP_START     	 0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  	  	 0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_W_NACK  		 0x20 /* Master transmit ( slave address + Write request ) to slave + No ACK received from slave. */
#define TWI_MT_DATA_W_ACK   	 0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MT_DATA_W_NACK  	 0x30 /* Master transmit data and NACK has been received from Slave. */
#define TWI_MT_ARBTRATION_LOST   0x38 /* Master lost Arbitration in SLA+W or DATA byte */

/* I2C Status Bits in the TWSR Register (Master Receiver) */
#define TWI_MR_START         	0x08 /* start has been sent */
#define TWI_MR_REP_START     	0x10 /* repeated start */
#define TWI_MR_ARBTRATION_LOST  0x38 /* Master lost Arbitration in SLA+R or NOT ACK bit */
#define TWI_MR_SLA_R_W_ACK  	0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MR_SLA_R_W_NACK  	0x48 /* Master transmit ( slave address + Read request ) to slave + No ACK received from slave. */
#define TWI_MR_DATA_W_ACK   	0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_W_NACK  	0x58 /* Master received data but doesn't send ACK to slave. */

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void TWI_init(const u8 copy_u8bitRate);
void TWI_sendStart(void);
void TWI_sendStop(void);
void TWI_sendByte(u8 copy_u8data);
void TWI_receiveByte_ACK(u8 * ptr);
void TWI_receiveByte_NoACK(u8 * ptr);
void TWI_getStatus(u8 * status);

#endif /* TWI_INT_H_ */
