/*
 * DCMOTOR_int.h
 *
 *  Created on: Nov 9, 2023
 *      Author: Ebram Habib
 */

#ifndef DCMOTOR_INT_H_
#define DCMOTOR_INT_H_

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void DcMotor_Init(void);

void DcMotor_ON(u8 speed);

void DcMotor_OFF(void);


#endif /* DCMOTOR_INT_H_ */
