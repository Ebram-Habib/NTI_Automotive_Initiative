/*
 * ADC_int.h
 *
 *  Created on: Oct 24, 2023
 *      Author: Ebram Habib
 */

#ifndef ADC_INT_H_
#define ADC_INT_H_

#include "std_types.h"
#include "ADC_config.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ADC_MAXIMUM_VALUE    1023
//#define ADC_REF_VOLT_VALUE   2.56
#define ADC_REF_VOLT_VALUE   5

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/


void ADC_Init(const ADC_INIT_CONFIG * adc_config);
u16 ADC_getDigitalValueSynchNonBlocking(u8 ADC_SINGLE_ENDED_CHANNELS);
void ADC_getDigitalValueAsynchCallBack(u8 ADC_SINGLE_ENDED_CHANNELS, void(*ptrfn)(u16));

#endif /* ADC_INT_H_ */
