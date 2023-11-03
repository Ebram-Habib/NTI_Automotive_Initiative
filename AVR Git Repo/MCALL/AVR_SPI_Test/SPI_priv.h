/*
 * SPI_priv.h
 *
 *  Created on: Oct 30, 2023
 *      Author: Ebram Habib
 */
#ifndef SPI_PRIV_H_
#define SPI_PRIV_H_

typedef union{
	struct{
		u8 SPR0_BIT : 1;
		u8 SPR1_BIT : 1;
		u8 CPHA_BIT : 1;
		u8 CPOL_BIT : 1;
		u8 MSTR_BIT : 1;
		u8 DORD_BIT : 1;
		u8 SPE_BIT : 1;
		u8 SPIE_BIT : 1;
	}bits;
	u8 FULL_REG;
}SPCR_REG;

typedef union{
	struct{
		u8 SPI2X_BIT : 1;
		u8 RESERVED : 5;
		u8 WCOL_BIT : 1;
		u8 SPIF_BIT : 1;
	}bits;
	u8 FULL_REG;
}SPSR_REG;



#define SPDR_REG *((volatile u8*) 0x2F)
#define SPSR_REG ((volatile SPSR_REG*) 0x2E)
#define SPCR_REG ((volatile SPCR_REG*) 0x2D)

#define SPSR_R *((volatile u8*) 0x2E)

/* SPCR */
#define SPIE    7
#define SPE     6
#define DORD    5
#define MSTR    4
#define CPOL    3
#define CPHA    2
#define SPR1    1
#define SPR0    0

/* SPSR */
#define SPIF    7
#define WCOL    6
/* bits 5-1 reserved */
#define SPI2X   0

#endif /* SPI_PRIV_H_ */
