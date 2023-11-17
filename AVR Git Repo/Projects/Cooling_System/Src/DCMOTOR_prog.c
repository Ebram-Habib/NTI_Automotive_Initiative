/*
 * DCMOTOR_prog.c
 *
 *  Created on: Nov 9, 2023
 *      Author: Ebram Habib
 */

#include "std_types.h"
#include "TIMER0_int.h"
#include "DCMOTOR_config.h"
#include "DCMOTOR_int.h"
#include "GPIO_Int.h"


/*******************************************************************************
 *                               Types Definition                             *
 *******************************************************************************/
TIMER0_INIT_CONFIG config = {
		TIMER0_COMPARE_OUTPUT_NON_PWM_MODE_OC0_DISCONNECTED,
		TIMER0_COMPARE_OUTPUT_FAST_PWM_MODE_OC0_CLEAR,
		TIMER0_COMPARE_OUTPUT_PHASE_CORRECT_PWM_MODE_OC0_DISCONNECTED,
		TIMER0_FCPU_DIVIDED_BY_1024,
		TIMER0_FAST_PWM_MODE,
		0,
		0 };

/*******************************************************************************
 *                      Functions Definition                                   *
 *******************************************************************************/

void DcMotor_Init(void)
{

	Timer0_Init(&config);

	/* Initializing the motor pins as outputs with 0 as initial value */
	DIO_voidSetPinDirection(DCMOTOR_PIN_1_PORT_ID, DCMOTOR_PIN_1_PIN_ID, output);
	DIO_voidSetPinDirection(DCMOTOR_PIN_2_PORT_ID, DCMOTOR_PIN_2_PIN_ID, output);
	DIO_voidSetPinValue(DCMOTOR_PIN_1_PORT_ID, DCMOTOR_PIN_1_PIN_ID, LOGIC_LOW);
	DIO_voidSetPinValue(DCMOTOR_PIN_2_PORT_ID, DCMOTOR_PIN_2_PIN_ID, LOGIC_LOW);
	/* Initialize the PWM pin OC0 */
	DIO_voidSetPinDirection(pPORTB, pin3, output);
}

void DcMotor_ON(u8 speed)
{
	DIO_voidSetPinValue(DCMOTOR_PIN_1_PORT_ID, DCMOTOR_PIN_1_PIN_ID, LOGIC_LOW);
	DIO_voidSetPinValue(DCMOTOR_PIN_2_PORT_ID, DCMOTOR_PIN_2_PIN_ID, LOGIC_HIGH);

	Timer0_Start(&config);
	Timer0_SetFastPWM(&config, speed);

}

void DcMotor_OFF(void)
{
	DIO_voidSetPinValue(DCMOTOR_PIN_1_PORT_ID, DCMOTOR_PIN_1_PIN_ID, LOGIC_LOW);
	DIO_voidSetPinValue(DCMOTOR_PIN_2_PORT_ID, DCMOTOR_PIN_2_PIN_ID, LOGIC_LOW);

	Timer0_SetFastPWM(&config, 0);
	Timer0_Stop(&config);
}
