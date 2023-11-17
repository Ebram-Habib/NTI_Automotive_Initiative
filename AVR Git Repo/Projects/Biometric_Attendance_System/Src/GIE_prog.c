/*
 * GIE_prog.c
 *
 *  Created on: Oct 22, 2023
 *      Author: Ebram Habib
 */

#include "GIE_priv.h"
#include "GIE_int.h"

void GIE_Enable(void)
{
	SREG_REG |= (1<<I_Bit);
}

void GIE_Disable(void)
{
	SREG_REG &= ~(1<<I_Bit);
}
