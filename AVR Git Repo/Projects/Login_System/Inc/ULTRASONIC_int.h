/*
 * ULTRASONIC_int.h
 *
 *  Created on: Oct 30, 2023
 *      Author: Ebram Habib
 */

#ifndef ULTRASONIC_INT_H_
#define ULTRASONIC_INT_H_

void Ultrasonic_edgeProcessing(void);
u16 Ultrasonic_readDistance(void);
void Ultrasonic_Trigger(void);
void Ultrasonic_init(void);
void Ultrasonic_disable(void);
void Ultrasonic_enable(void);

#endif /* ULTRASONIC_INT_H_ */
