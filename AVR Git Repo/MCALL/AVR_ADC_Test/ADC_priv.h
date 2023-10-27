/*
 * ADC_priv.h
 *
 *  Created on: Oct 24, 2023
 *      Author: Ebram Habib
 */

#ifndef ADC_PRIV_H_
#define ADC_PRIV_H_

typedef union{
	struct{
	u8 MUX0_BIT : 1;
	u8 MUX1_BIT : 1;
	u8 MUX2_BIT : 1;
	u8 MUX3_BIT : 1;
	u8 MUX4_BIT : 1;
	u8 ADLAR_BIT : 1;
	u8 REFS0_BIT : 1;
	u8 REFS1_BIT : 1;
}bits;
	u8 FULL_REG;
}ADMUX_REG;

typedef union{

	 struct{
	u8 ADPS0_BIT : 1;
	u8 ADPS1_BIT : 1;
	u8 ADPS2_BIT : 1;
	u8 ADIE_BIT : 1;
	u8 ADIF_BIT : 1;
	u8 ADATE_BIT : 1;
	u8 ADSC_BIT : 1;
	u8 ADEN_BIT : 1;
	}bits;
	u8 FULL_REG;
}ADCSRA_REG;

typedef union{
	struct{
	u8 PSR10_BIT : 1;
	u8 PSR2_BIT : 1;
	u8 PUD_BIT : 1;
	u8 ACME_BIT : 1;
	u8 RESERVED_BIT : 1;
	u8 ADTS0_BIT : 1;
	u8 ADTS1_BIT : 1;
	u8 ADTS2_BIT : 1;
	}bits;
	u8 FULL_REG;
}SFIOR_REG;

#define ADMUX_REG	((volatile ADMUX_REG*) 0x27)
#define ADCSRA_REG	((volatile ADCSRA_REG*) 0x26)
#define SFIOR_REG	((volatile SFIOR_REG*) 0x50)
//#define ADMUX_REG	*((volatile ADMUX) 0x27)
//#define ADCSRA_REG	*((volatile ADCSRA) 0x26)
//#define SFIOR_REG	*((volatile SFIOR) 0x50)
#define ADCH	*((volatile u8*) 0x25)
#define ADCL	*((volatile u8*) 0x24)

#endif /* ADC_PRIV_H_ */
