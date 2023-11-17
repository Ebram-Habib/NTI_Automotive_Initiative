/*
 * LM35_SENSOR_prog.c
 *
 *  Created on: Nov 9, 2023
 *      Author: Ebram Habib
 */

#include "std_types.h"
#include "LM35_SENSOR_int.h"
#include "LM35_SENSOR_config.h"
#include "LM35_SENSOR_priv.h"
#include "ADC_int.h"

/* Global Variables */
u16 adc_value = 0;
ADC_INIT_CONFIG adc_config = {ADC_INT_ENABLE, AVCC, DIVISION_FACTOR_64, RIGHT_ADJUST};

/* Initializing the ADC */
void LM35_SENSOR_init(void)
{
	ADC_Init(&adc_config);
	/* Read ADC channel where the temperature sensor is connected using callback function */
	ADC_getDigitalValueAsynchCallBack(SENSOR_CHANNEL_ID, valueUpdate);
}

/*
 * Description :
 * Function responsible for calculate the temperature from the ADC digital value.
 */
u8 LM35_SENSOR_getTemperature(void)
{
	u8 temp_value = 0;


	/* Calculate the temperature from the ADC value*/
	temp_value = (u8)(((u32)adc_value*SENSOR_MAX_TEMPERATURE*ADC_REF_VOLT_VALUE)/(ADC_MAXIMUM_VALUE*SENSOR_MAX_VOLT_VALUE));

	return temp_value;
}

void valueUpdate(u16 val)
{

	adc_value = val;
}
