/*
 * TIMER1_config.h
 *
 *  Created on: Oct 28, 2023
 *      Author: Ebram Habib
 */

#ifndef TIMER1_CONFIG_H_
#define TIMER1_CONFIG_H_

typedef enum{
	TIMER1_NORMAL_MODE,
	TIMER1_PHASE_CORRECT_PWM_8bIT_MODE,
	TIMER1_PHASE_CORRECT_PWM_9bIT_MODE,
	TIMER1_PHASE_CORRECT_PWM_10bIT_MODE,
	TIMER1_CTC_OCR1A_MODE,
	TIMER1_FAST_PWM_8bIT_MODE,
	TIMER1_FAST_PWM_9bIT_MODE,
	TIMER1_FAST_PWM_10bIT_MODE,
	TIMER1_PHASE_FREQUENCY_CORRECT_PWM_ICR1_MODE,
	TIMER1_PHASE_FREQUENCY_CORRECT_PWM_OCR1A_MODE,
	TIMER1_PHASE_CORRECT_PWM_ICR1_MODE,
	TIMER1_PHASE_CORRECT_PWM_OCR1A_MODE,
	TIMER1_CTC_ICR1_MODE,
	Reserved,
	TIMER1_FAST_PWM_ICR1_MODE,
	TIMER1_FAST_PWM_OCR1A_MODE,
}TIMER1_MODE;

typedef enum{
	TIMER1_COMPARE_OUTPUT_NON_PWM_MODE_OC1A_OC1B_DISCONNECTED,
	TIMER1_COMPARE_OUTPUT_NON_PWM_MODE_OC1A_OC1B_TOGGLE,
	TIMER1_COMPARE_OUTPUT_NON_PWM_MODE_OC1A_OC1B_CLEAR,
	TIMER1_COMPARE_OUTPUT_NON_PWM_MODE_OC1A_OC1B_SET
}TIMER1_COMPARE_OUTPUT_NON_PWM_MODE;

typedef enum{
	TIMER1_COMPARE_OUTPUT_FAST_PWM_MODE_OC1A_OC1B_DISCONNECTED,
	TIMER1_COMPARE_OUTPUT_FAST_PWM_MODE_OC1A_TOGGLE,
	TIMER1_COMPARE_OUTPUT_FAST_PWM_MODE_OC1A_OC1B_CLEAR,
	TIMER1_COMPARE_OUTPUT_FAST_PWM_MODE_OC1A_OC1B_SET
}TIMER1_COMPARE_OUTPUT_FAST_PWM_MODE;

typedef enum{
	TIMER1_COMPARE_OUTPUT_PHASE_CORRECT_PWM_MODE_OC1A_OC1B_DISCONNECTED,
	TIMER1_COMPARE_OUTPUT_PHASE_CORRECT_PWM_MODE_OC1A_TOGGLE,
	TIMER1_COMPARE_OUTPUT_PHASE_CORRECT_PWM_MODE_OC1A_OC1B_CLEAR,
	TIMER1_COMPARE_OUTPUT_PHASE_CORRECT_PWM_MODE_OC1A_OC1B_SET
}TIMER1_COMPARE_OUTPUT_PHASE_CORRECT_PWM_MODE;

typedef enum{
	FCPU_DIVIDED_BY_1=1,
	FCPU_DIVIDED_BY_8,
	FCPU_DIVIDED_BY_64,
	FCPU_DIVIDED_BY_256,
	FCPU_DIVIDED_BY_1024,
	EXTERNAL_SOURCE_FALLING_EDGE,
	EXTERNAL_SOURCE_RISING_EDGE
}TIMER1_CLOCK_SELECT;


typedef struct{
	TIMER1_COMPARE_OUTPUT_NON_PWM_MODE 				Compare_output_Non_PWM;
	TIMER1_COMPARE_OUTPUT_FAST_PWM_MODE				Compare_output_Fast_PWM;
	TIMER1_COMPARE_OUTPUT_PHASE_CORRECT_PWM_MODE	Compare_output_Phase_Correct_PWM;
	TIMER1_CLOCK_SELECT 							Clock_Select;
	TIMER1_MODE 									Mode;
	u16 TIMER1_INITIAL_VALUE;
	u16 TIMER1_COMPARE_VALUE;
}TIMER1_INIT_CONFIG;

#define TICK_TIME 4

#endif /* TIMER1_CONFIG_H_ */
