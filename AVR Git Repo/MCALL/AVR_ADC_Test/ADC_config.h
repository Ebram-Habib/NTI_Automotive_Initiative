/*
 * ADC_config.h
 *
 *  Created on: Oct 24, 2023
 *      Author: Ebram Habib
 */

#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_

typedef enum{
ADC_INT_ENABLE = 1, ADC_INT_DISABLE = 0, ADC_FREE_RUNNINC = 2, ADC_AUTO_TRIGGER = 3
}ADC_MODE;

typedef enum{
	ADC0 = 0, ADC1 = 1, ADC2 = 2, ADC3 = 3, ADC4 = 4, ADC5 = 5, ADC6 = 6, ADC7 = 7
}ADC_SINGLE_ENDED_CHANNELS;

typedef enum{
	AREF = 0, AVCC = 1, INTERNAL_VOLTAGE = 3
}ADC_VOLT_REF;

typedef enum{
LEFT_ADJUST = 1, RIGHT_ADJUST = 0
}ADC_RESULT_ADJUST_DIR;

typedef enum{
	DIVISION_FACTOR_2=1,DIVISION_FACTOR_4,DIVISION_FACTOR_8,DIVISION_FACTOR_16,DIVISION_FACTOR_32,DIVISION_FACTOR_64,DIVISION_FACTOR_128
}ADC_PRESCALER;

typedef struct{
	ADC_VOLT_REF Volt_Ref;
	ADC_RESULT_ADJUST_DIR Result_Direction_Adjust;
	ADC_PRESCALER Prescaler;
	ADC_MODE Mode;

}ADC_INIT_CONFIG;

#endif /* ADC_CONFIG_H_ */
