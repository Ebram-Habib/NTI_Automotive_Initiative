/*
 * TWI_prog.c
 *
 *  Created on: Oct 31, 2023
 *      Author: Ebram Habib
 */

#include "std_types.h"
#include "TWI_config.h"
#include "TWI_int.h"
#include "TWI_priv.h"

void TWI_init(const u8 copy_u8bitRate)
{
	/* Bit Rate: 100 or 400kbps using zero pre-scaler TWPS=00 and F_CPU=16Mhz */
	    TWBR_REG = copy_u8bitRate;
		TWSR_REG = 0x00;

	    TWCR_REG = (1<<TWEN); /* enable TWI */

}
void TWI_sendStart(void)
{
    TWCR_REG = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); /* enable TWI, set the flag, and send star */
    while (!(TWCR_REG & (1<<TWINT)));
}
void TWI_sendStop(void)
{
    TWCR_REG = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN); /* enable TWI, set the flag, and send star */
}
void TWI_sendByte(u8 copy_u8data)
{
	/* Put data On TWI data Register */
	    TWDR_REG = copy_u8data;
	    /*
		 * Clear the TWINT flag before sending the data TWINT=1
		 * Enable TWI Module TWEN=1
		 */
	    TWCR_REG = (1 << TWINT) | (1 << TWEN);
	    /* Wait for TWINT flag set in TWCR Register(data is send successfully) */
	    while (!(TWCR_REG & (1<<TWINT)));

}
void TWI_receiveByte_ACK(u8 * ptr)
{
		/*
		 * Clear the TWINT flag before reading the data TWINT=1
		 * Enable sending ACK after reading or receiving data TWEA=1
		 * Enable TWI Module TWEN=1
		 */
	    TWCR_REG = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
	    while (!(TWCR_REG & (1<<TWINT)));
	    /* Read Data */
	    *ptr = TWDR_REG;
}
void TWI_receiveByte_NoACK(u8 * ptr)
{
		/*
		 * Clear the TWINT flag before reading the data TWINT=1
		 * Enable TWI Module TWEN=1
		 */
		    TWCR_REG = (1 << TWINT) | (1 << TWEN) ;
		    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
		    while (!(TWCR_REG & (1<<TWINT)));
		    /* Read Data */
		    *ptr = TWDR_REG;
}
void TWI_getStatus(u8 * status)
{
	*status = (TWSR_REG & TWI_ERROR_STATUS_MASK);
}
