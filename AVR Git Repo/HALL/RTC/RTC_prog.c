/*
 * RTC_prog.c
 *
 *  Created on: Nov 3, 2023
 *      Author: Ebram Habib
 */

#include "std_types.h"
#include "RTC_int.h"
#include "RTC_config.h"
#include "RTC_priv.h"
#include "TWI_int.h"

u8 status = 0;

void RTC_init(void)
{
	TWI_init(TWI_CLK_RATE_100K_FCPU16MHZ);
}
u8 RTC_setTime(RTC_TIME* time_config_ptr)
{
	u8 val = 0;

	TWI_sendStart();
	TWI_getStatus(&status);
	if (status != TWI_MT_START)
		return ERROR;

	TWI_sendByte(RTC_SLAVE_ADDRESS | WRITE);
	TWI_getStatus(&status);
	if (status != TWI_MT_SLA_W_ACK)
		return ERROR;

	TWI_sendByte(RTC_POINTER_TIME_ADDRESS);
	TWI_getStatus(&status);
	if (status != TWI_MT_DATA_W_ACK)
		return ERROR;

	val = RTC_decimalToBCD(time_config_ptr->seconds);
	TWI_sendByte(val);
	TWI_getStatus(&status);
	if (status != TWI_MT_DATA_W_ACK)
		return ERROR;

	val = 0;

	val = RTC_decimalToBCD(time_config_ptr->minuets);
	TWI_sendByte(val);
	TWI_getStatus(&status);
	if (status != TWI_MT_DATA_W_ACK)
		return ERROR;

	val = 0;

	val = RTC_decimalToBCD(time_config_ptr->hours);
	if(time_config_ptr->HOURS_MODE == TWENTYFOUD_HOURS)
	{

	}
	else if(time_config_ptr->HOURS_MODE == TWELVE_HOURS)
	{
		if(time_config_ptr->AMPM_MODE == PM)
		{
			val |= (1<<5) | (1<<6);
		}
		else if(time_config_ptr->AMPM_MODE == AM)
		{
			val |= (1<<6);
		}
	}
	TWI_sendByte(val);
	TWI_getStatus(&status);
	if (status != TWI_MT_DATA_W_ACK)
		return ERROR;

	TWI_sendStop();
	return SUCCESS;
}
u8 RTC_getTime(RTC_TIME* time_config_ptr)
{
	u8 val = 0;

	TWI_sendStart();
	TWI_getStatus(&status);
	if (status != TWI_MT_START)
		return ERROR;

	TWI_sendByte(RTC_SLAVE_ADDRESS | WRITE);
	TWI_getStatus(&status);
	if (status != TWI_MT_SLA_W_ACK)
		return ERROR;

	TWI_sendByte(RTC_POINTER_TIME_ADDRESS);
	TWI_getStatus(&status);
	if (status != TWI_MT_DATA_W_ACK)
		return ERROR;

	TWI_sendStart();
	TWI_getStatus(&status);
	if (status != TWI_MR_REP_START)
		return ERROR;

	TWI_sendByte(RTC_SLAVE_ADDRESS | READ);
	TWI_getStatus(&status);
	if (status != TWI_MR_SLA_R_W_ACK)
		return ERROR;

	TWI_receiveByte_ACK(&val);
	TWI_getStatus(&status);
	if (status != TWI_MR_DATA_W_ACK)
		return ERROR;
	time_config_ptr->seconds =  RTC_BCDdecimal(val);

	val = 0;

	TWI_receiveByte_ACK(&val);
	TWI_getStatus(&status);
	if (status != TWI_MR_DATA_W_ACK)
		return ERROR;
	time_config_ptr->minuets =  RTC_BCDdecimal(val);

	val = 0;

	TWI_receiveByte_NoACK(&val);
	TWI_getStatus(&status);
	if (status != TWI_MR_DATA_W_NACK)
		return ERROR;

	if(time_config_ptr->HOURS_MODE == TWENTYFOUD_HOURS)
	{
		time_config_ptr->hours =  RTC_BCDdecimal(val);
	}
	else if(time_config_ptr->HOURS_MODE == TWELVE_HOURS)
	{
		if(time_config_ptr->AMPM_MODE == PM)
		{
			val &= (1<<5);
			val &= ~(1<<6);
			time_config_ptr->hours =  RTC_BCDdecimal(val);
		}
		else if(time_config_ptr->AMPM_MODE == AM)
		{
			val &= ~(1<<6);
			time_config_ptr->hours =  RTC_BCDdecimal(val);
		}
	}

	TWI_sendStop();
	return SUCCESS;

}
u8 RTC_setDate(RTC_DATE* date_config_ptr)
{
	u8 val = 0;

	TWI_sendStart();
	TWI_getStatus(&status);
	if (status != TWI_MT_START)
		return ERROR;

	TWI_sendByte(RTC_SLAVE_ADDRESS | WRITE);
	TWI_getStatus(&status);
	if (status != TWI_MT_SLA_W_ACK)
		return ERROR;

	TWI_sendByte(RTC_POINTER_DATE_ADDRESS);
	TWI_getStatus(&status);
	if (status != TWI_MT_DATA_W_ACK)
		return ERROR;

	val = RTC_decimalToBCD(date_config_ptr->DAY);
	TWI_sendByte(val);
	TWI_getStatus(&status);
	if (status != TWI_MT_DATA_W_ACK)
		return ERROR;

	val = 0;

	val = RTC_decimalToBCD(date_config_ptr->date);
	TWI_sendByte(val);
	TWI_getStatus(&status);
	if (status != TWI_MT_DATA_W_ACK)
		return ERROR;

	val = 0;

	val = RTC_decimalToBCD(date_config_ptr->month);
	TWI_sendByte(val);
	TWI_getStatus(&status);
	if (status != TWI_MT_DATA_W_ACK)
		return ERROR;

	val = 0;

	val = RTC_decimalToBCD(date_config_ptr->year);
	TWI_sendByte(val);
	TWI_getStatus(&status);
	if (status != TWI_MT_DATA_W_ACK)
		return ERROR;

	TWI_sendStop();
	return SUCCESS;
}
u8 RTC_getDate(RTC_DATE* date_config_ptr)
{
	u8 val = 0;

	TWI_sendStart();
	TWI_getStatus(&status);
	if (status != TWI_MT_START)
		return ERROR;

	TWI_sendByte(RTC_SLAVE_ADDRESS | WRITE);
	TWI_getStatus(&status);
	if (status != TWI_MT_SLA_W_ACK)
		return ERROR;

	TWI_sendByte(RTC_POINTER_DATE_ADDRESS);
	TWI_getStatus(&status);
	if (status != TWI_MT_DATA_W_ACK)
		return ERROR;

	TWI_sendStart();
	TWI_getStatus(&status);
	if (status != TWI_MR_REP_START)
		return ERROR;

	TWI_sendByte(RTC_SLAVE_ADDRESS | READ);
	TWI_getStatus(&status);
	if (status != TWI_MR_SLA_R_W_ACK)
		return ERROR;

	TWI_receiveByte_ACK(&val);
	TWI_getStatus(&status);
	if (status != TWI_MR_DATA_W_ACK)
		return ERROR;
	date_config_ptr->DAY =  RTC_BCDdecimal(val);

	val = 0;

	TWI_receiveByte_ACK(&val);
	TWI_getStatus(&status);
	if (status != TWI_MR_DATA_W_ACK)
		return ERROR;
	date_config_ptr->date =  RTC_BCDdecimal(val);

	val = 0;

	TWI_receiveByte_ACK(&val);
	TWI_getStatus(&status);
	if (status != TWI_MR_DATA_W_ACK)
		return ERROR;
	date_config_ptr->month =  RTC_BCDdecimal(val);

	val = 0;

		TWI_receiveByte_NoACK(&val);
		TWI_getStatus(&status);
		if (status != TWI_MR_DATA_W_NACK)
			return ERROR;
		date_config_ptr->year =  RTC_BCDdecimal(val);

	TWI_sendStop();
	return SUCCESS;

}

static u8 RTC_decimalToBCD(u8 val)
{
	u8 newval = 0, first_half = 0, second_half = 0;

	if(val == 0)
	{
		return 0;
	}
	else
	{
		first_half = val%10;
		val /=10;
		second_half = val%10;
		newval = second_half;
		newval <<= 4;
		newval |= first_half;
		return newval;
	}
}

static u8 RTC_BCDdecimal(u8 val)
{
	u8 newval = 0;

	newval = (val & 0xF0);
	newval *= 10;
	newval += (val & 0x0F);
	return newval;
}
