/*
 * TIMER1_priv.h
 *
 *  Created on: Oct 28, 2023
 *      Author: Ebram Habib
 */

#ifndef TIMER1_PRIV_H_
#define TIMER1_PRIV_H_

typedef union{
	struct{
		u8 WGM10_BIT : 1;
		u8 WGM11_BIT : 1;
		u8 FOC1B_BIT : 1;
		u8 FOC1A_BIT : 1;
		u8 COM1B0_BIT : 1;
		u8 COM1B1_BIT : 1;
		u8 COM1A0_BIT : 1;
		u8 COM1A1_BIT : 1;
	}bits;
	u8 FULL_REG;
}TCCR1A_REG;

typedef union{
	struct{
		u8 CS10_BIT : 1;
		u8 CS11_BIT : 1;
		u8 CS12_BIT : 1;
		u8 WGM12_BIT : 1;
		u8 WGM13_BIT: 1;
		u8 RESERVED : 1;
		u8 ICES1_BIT: 1;
		u8 ICNC1_BIT: 1;
	}bits;
	u8 FULL_REG;
}TCCR1B_REG;

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


#define TCCR1A_REG	((volatile TCCR1A_REG*) 0x4F)
#define TCCR1B_REG	((volatile TCCR1B_REG*) 0x4E)
#define TIMSK_REG	((volatile TIMSK_REG*) 0x59)
#define TIFR_REG	((volatile TIFR_REG*) 0x58)
#define TCNT1H_REG	*((volatile u8*) 0x4D)
#define TCNT1L_REG	*((volatile u8*) 0x4C)
#define OCR1AH_REG	*((volatile u8*) 0x4B)
#define OCR1AL_REG	*((volatile u8*) 0x4A)
#define OCR1BH_REG	*((volatile u8*) 0x49)
#define OCR1BL_REG	*((volatile u8*) 0x48)
#define ICR1H_REG	*((volatile u8*) 0x47)
#define ICR1L_REG	*((volatile u8*) 0x46)

#define CLOCK_SELECT_MASK	0xF8
#define NO_CLOCK			0
#define OVF_INTERRUPT		0
#define CTC_INTERRUPT		1
#define TOP_VALUE			65535
#define RISING_EDGE			1
#define FALLING_EDGE		0

#endif /* TIMER1_PRIV_H_ */
