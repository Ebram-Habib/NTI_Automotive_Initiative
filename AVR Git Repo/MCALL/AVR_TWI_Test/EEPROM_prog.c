/*
 * EEPROM_prog.c
 *
 *  Created on: Nov 1, 2023
 *      Author: Ebram Habib
 */
#include "EEPROM_int.h"
#include "EEPROM_priv.h"
#include "EEPROM_config.h"
#include "TWI_int.h"

u8 status = 0;

void EEPROM_init(void)
{
	TWI_init(TWI_CLK_RATE_400K_FCPU16MHZ);
}

u8 EEPROM_writeByte(u16 u16addr,u8 u8data)
{
	/* Send the Start Bit */
	TWI_sendStart();
	TWI_getStatus(&status);
	if (status != TWI_MR_START)
		return ERROR;

	/* Send the device address, we need to get A8 A9 A10 address bits from the
	 * memory location address and R/W=0 (write) */
	TWI_sendByte((u8)(EEPROM_BASE_ADDRESS | ((u16addr & 0x0700)>>7)));
	TWI_getStatus(&status);
	if (status != TWI_MT_SLA_W_ACK)
		return ERROR;

	/* Send the required memory location address */
	TWI_sendByte((u8)(u16addr));
	TWI_getStatus(&status);
	if (status != TWI_MT_DATA_W_ACK)
		return ERROR;

	/* write byte to eeprom */
	TWI_sendByte(u8data);
	TWI_getStatus(&status);
	if (status != TWI_MT_DATA_W_ACK)
		return ERROR;

	/* Send the Stop Bit */
	TWI_sendStop();

	return SUCCESS;
}

u8 EEPROM_readByte(u16 u16addr,u8 *u8data)
{
	/* Send the Start Bit */
	TWI_sendStart();
	TWI_getStatus(&status);
	if (status != TWI_MR_START)
		return ERROR;

	/* Send the device address, we need to get A8 A9 A10 address bits from the
	 * memory location address and R/W=0 (write) */
	TWI_sendByte((u8)((EEPROM_BASE_ADDRESS) | ((u16addr & 0x0700)>>7)));
	TWI_getStatus(&status);
	if (status != TWI_MT_SLA_W_ACK)
		return ERROR;

	/* Send the required memory location address */
	TWI_sendByte((u8)(u16addr));
	TWI_getStatus(&status);
	if (status != TWI_MT_DATA_W_ACK)
		return ERROR;

	/* Send the Repeated Start Bit */
	TWI_sendStart();
	TWI_getStatus(&status);
	if (status != TWI_MT_REP_START)
		return ERROR;

	/* Send the device address, we need to get A8 A9 A10 address bits from the
	 * memory location address and R/W=1 (Read) */
	TWI_sendByte((u8)((EEPROM_BASE_ADDRESS) | ((u16addr & 0x0700)>>7) | 1));
	TWI_getStatus(&status);
	if (status != TWI_MR_SLA_R_W_ACK)
		return ERROR;

	/* Read Byte from Memory without send ACK */
	TWI_receiveByte_NoACK(u8data);
	TWI_getStatus(&status);
	if (status != TWI_MR_DATA_W_NACK)
		return ERROR;

	/* Send the Stop Bit */
	TWI_sendStop();

	return SUCCESS;
}

