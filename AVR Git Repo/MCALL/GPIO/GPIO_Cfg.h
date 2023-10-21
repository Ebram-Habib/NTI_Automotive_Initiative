/*
 * GPIO_Cfg.h
 *
 *  Created on: Oct 20, 2023
 *      Author: Ebram Habib
 */

#ifndef GPIO_CFG_H_
#define GPIO_CFG_H_

typedef enum
{
	Pin0,pin1,pin2,pin3,pin4,pin5,pin6,pin7
}PIN_ID;

typedef enum
{
	input,output
}DIRECTION;

typedef enum
{
	low,high
}PIN_VAL;

typedef union {
	struct {

		u8 bit0 : 1;
		u8 bit1 : 1;
		u8 bit2 : 1;
		u8 bit3 : 1;
		u8 bit4 : 1;
		u8 bit5 : 1;
		u8 bit6 : 1;
		u8 bit7 : 1;
	}bits;
	u8 Full_Reg;
}Reg;

typedef struct {
	Reg PIN_reg;
	Reg DDR_reg;
	Reg PORT_reg;
}port;


extern port* const pPORTA;
extern port* const pPORTB;
extern port* const pPORTC;
extern port* const pPORTD;

#endif /* GPIO_CFG_H_ */
