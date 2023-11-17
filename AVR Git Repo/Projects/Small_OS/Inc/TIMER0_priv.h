/*
 * TIMER0_priv.h
 *
 *  Created on: Oct 27, 2023
 *      Author: Ebram Habib
 */

#ifndef TIMER0_PRIV_H_
#define TIMER0_PRIV_H_

typedef union{
	struct{
		u8 CS00_BIT : 1;
		u8 CS01_BIT : 1;
		u8 CS02_BIT : 1;
		u8 WGM01_BIT : 1;
		u8 COM00_BIT : 1;
		u8 COM01_BIT : 1;
		u8 WGM00_BIT : 1;
		u8 FOC0_BIT : 1;
	}bits;
	u8 FULL_REG;
}TCCR0_REG;

typedef union{
	struct{
		u8 TOIE0_BIT : 1;
		u8 OCIE0_BIT : 1;
		u8 TOIE1_BIT : 1;
		u8 OCIE1B_BIT : 1;
		u8 OCIE1A_BIT : 1;
		u8 TICIE1_BIT : 1;
		u8 TOIE2_BIT : 1;
		u8 OCIE2_BIT : 1;
	}bits;
	u8 FULL_REG;
}TIMSK_REG;

typedef union{
	struct{
		u8 TOV0_BIT : 1;
		u8 OCF0_BIT : 1;
		u8 TOV1_BIT : 1;
		u8 OCF1B_BIT : 1;
		u8 OCF1A_BIT : 1;
		u8 ICF1_BIT : 1;
		u8 TOV2_BIT : 1;
		u8 OCF2_BIT : 1;
	}bits;
	u8 FULL_REG;
}TIFR_REG;


#define TCCR0_REG	((volatile TCCR0_REG*) 0x53)
#define TIMSK_REG	((volatile TIMSK_REG*) 0x59)
#define TIFR_REG	((volatile TIFR_REG*) 0x58)
#define TCNT0_REG	*((volatile u8*) 0x52)
#define OCR0_REG	*((volatile u8*) 0x5C)

#define CLOCK_SELECT_MASK	0xF8
#define NO_CLOCK			0
#define OVF_INTERRUPT		0
#define CTC_INTERRUPT		1
#define TOP_VALUE			256

#endif /* TIMER0_PRIV_H_ */
