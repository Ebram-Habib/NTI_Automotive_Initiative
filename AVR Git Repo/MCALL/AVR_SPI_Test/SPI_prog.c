/*
 * SPI_prog.c
 *
 *  Created on: Oct 30, 2023
 *      Author: Ebram Habib
 */
#include "std_types.h"
#include "common_macros.h"
#include "SPI_int.h"
#include "SPI_config.h"
#include "SPI_priv.h"
#include "avr/interrupt.h"

/*******************************************************************************
 *                      Global Variables	                                   *
 *******************************************************************************/
static void(*ptrCallBack)(u8) = NULL_PTR;


void SPI_init(const SPI_INIT_CONFIG* Config_Ptr)
{
	u8 regValue = 0;
		regValue = (SPI_ENABLE<<SPE) | ((Config_Ptr->spi_data_order)<<DORD) | ((Config_Ptr->spi_master_slave_select)<<MSTR) | ((Config_Ptr->spi_clock_polarity)<<CPOL) | ((Config_Ptr->spi_clock_phase)<<CPHA);
		if((Config_Ptr->spi_speed_mode) == 0)
		{
			regValue |= ((((Config_Ptr->spi_clock_rate_select) & 0x02) >>1)<<SPR1) | (((Config_Ptr->spi_clock_rate_select) & 0x01)<<SPR0);
			SPCR_REG->FULL_REG = regValue;
		}
		else if((Config_Ptr->spi_speed_mode) == 1)
		{
			regValue |= ((((Config_Ptr->spi_clock_rate_select) & 0x02) >>1)<<SPR1) | (((Config_Ptr->spi_clock_rate_select) & 0x01)<<SPR0);
			SPCR_REG->FULL_REG = regValue;
			SPSR_REG->bits.SPI2X_BIT =  (((Config_Ptr->spi_clock_rate_select) & 0x04)>>2);
		}
}
void SPI_intEnable(void)
{
	SPCR_REG->bits.SPIE_BIT = SPI_ENABLE;
}
void SPI_intDisable(void)
{
	SPCR_REG->bits.SPIE_BIT = SPI_DISABLE;
}
void SPI_transferSynchBlocking(u8 send, u8* receive)
{
	SPDR_REG = send;
	while(!(SPSR_REG->bits.SPIF_BIT));
	*receive = SPDR_REG;
}
void SPI_transferAsynchCallBack(u8 send)
{
	SPDR_REG = send;

}
void SPI_SetCallBack(void(*ptrfn)(u8))
{
	ptrCallBack = ptrfn;
}

ISR(SPI_STC_vect)
{
	static u8 byte = 0;
	byte = SPDR_REG;

	if(ptrCallBack != NULL_PTR)
	{
		(*ptrCallBack)(byte);
	}
}
