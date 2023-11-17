/*
 * LM35_SENSOR_int.h
 *
 *  Created on: Nov 9, 2023
 *      Author: Ebram Habib
 */

#ifndef LM35_SENSOR_INT_H_
#define LM35_SENSOR_INT_H_

#include "std_types.h"


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/


/*
 * Description :
 * Function responsible for initialize the LM35 temperature sensor
 */

void LM35_SENSOR_init(void);

/*
 * Description :
 * Function responsible for calculate the temperature from the ADC digital value.
 */
u8 LM35_SENSOR_getTemperature(void);

#endif /* LM35_SENSOR_INT_H_ */
