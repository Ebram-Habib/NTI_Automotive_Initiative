/*
 * ADC_prog.c
 *
 *  Created on: Oct 24, 2023
 *      Author: Ebram Habib
 */

#include "std_types.h"
#include "ADC_config.h"
#include "ADC_int.h"
#include "ADC_priv.h"
#include <avr/interrupt.h>

static void(*ptrCallBack)(u16) = NULL_PTR;
static u16 value = 0;

void ADC_Init(const ADC_INIT_CONFIG* adc_config)
{

	ADMUX_REG->FULL_REG = ((ADMUX_REG->FULL_REG & 0x3F)|(adc_config->Volt_Ref << 6));

//	ADMUX_REG->bits.REFS1_BIT = (adc_config->Volt_Ref >> 1);
//	ADMUX_REG->bits.REFS0_BIT = (adc_config->Volt_Ref);
//	ADMUX_REG->bits.ADLAR_BIT = (adc_config->Result_Direction_Adjust);

	ADCSRA_REG->bits.ADEN_BIT = LOGIC_HIGH;
	ADCSRA_REG->FULL_REG = ((ADCSRA_REG->FULL_REG & 0xF8)|(adc_config->Prescaler));

//	ADCSRA_REG->bits.ADPS0_BIT = (adc_config->Prescaler);
//	ADCSRA_REG->bits.ADPS1_BIT = (adc_config->Prescaler >> 1);
//	ADCSRA_REG->bits.ADPS2_BIT = (adc_config->Prescaler >> 2);

	switch(adc_config->Mode)
	{
	case 	ADC_INT_ENABLE:
		ADCSRA_REG->bits.ADIE_BIT = LOGIC_HIGH;
		break;
	case	ADC_INT_DISABLE:
		ADCSRA_REG->bits.ADIE_BIT = LOGIC_LOW;
		break;
	case 	ADC_FREE_RUNNINC:
		/* adjust SFIOR accordingly */
		break;
	case 	ADC_AUTO_TRIGGER:
		ADCSRA_REG->bits.ADATE_BIT = LOGIC_HIGH;
		/* adjust SFIOR accordingly */
		break;
	}


}

u16 ADC_getDigitalValueSynchNonBlocking(u8 ADC_SINGLE_ENDED_CHANNELS)
{

	ADMUX_REG->FULL_REG |= (0x1F & ADC_SINGLE_ENDED_CHANNELS);

	ADCSRA_REG->bits.ADSC_BIT = LOGIC_HIGH;

	if(ADCSRA_REG->bits.ADIF_BIT == LOGIC_HIGH)
	{
		if(ADMUX_REG->bits.ADLAR_BIT == LOGIC_LOW)
		{
			value = (0x03 & ADCH);
			value = (value << 8);
			value |= ADCL;
		}
		else if(ADMUX_REG->bits.ADLAR_BIT == LOGIC_HIGH)
		{
			value = ADCH;
			value = ((ADCL>> 6) | (value << 8));
		}
		ADCSRA_REG->bits.ADEN_BIT = LOGIC_LOW;
		ADCSRA_REG->bits.ADIF_BIT = LOGIC_HIGH;

		return value;
	}
	return value;
}
void ADC_getDigitalValueAsynchCallBack(u8 ADC_SINGLE_ENDED_CHANNELS, void(*ptrfn)(u16))
{
	ADMUX_REG->FULL_REG |= (0x1F & ADC_SINGLE_ENDED_CHANNELS);

	ADCSRA_REG->bits.ADIE_BIT = LOGIC_HIGH;
	ptrCallBack = ptrfn;
	ADCSRA_REG->bits.ADSC_BIT = LOGIC_HIGH;
}

ISR(ADC_vect)
{


	if(ADMUX_REG->bits.ADLAR_BIT == LOGIC_LOW)
	{
//		value = (0x03 & ADCH);
//		value = (value << 8);
//		value |= ADCL;
		value = ADC_REG;
	}
	else if(ADMUX_REG->bits.ADLAR_BIT == LOGIC_HIGH)
	{
//		value = ADCH;
//		value = ((ADCL>> 6) | (value << 8));
		value = ADC_REG;
	}

	if(ptrCallBack != NULL_PTR)
	{
		ptrCallBack(value);
		ADCSRA_REG->bits.ADSC_BIT = LOGIC_HIGH;
	}
}

