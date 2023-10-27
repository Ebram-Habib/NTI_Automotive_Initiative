/*
 * EXTI_priv.h
 *
 *  Created on: Oct 22, 2023
 *      Author: Ebram Habib
 */

#ifndef EXTI_PRIV_H_
#define EXTI_PRIV_H_

#include "std_types.h"

#define MCUCR *((volatile u8*) 0x55)
#define MCUCSR *((volatile u8*) 0x54)
#define GICR *((volatile u8*) 0x5A)

#endif /* EXTI_PRIV_H_ */
