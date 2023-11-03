/*
 * LCD_prog.c
 *
 *  Created on: Oct 23, 2023
 *      Author: Ebram Habib
 */

#include "std_types.h"
#include "LCD_int.h"
#include "LCD_priv.h"
#include "GPIO_Int.h"
#include "LCD_config.h"
#include <util/delay.h>
#include <stdlib.h>


u8 u8LCD_DataPins[4] = {LCD_D4_PIN,LCD_D5_PIN,LCD_D6_PIN,LCD_D7_PIN};
s8 digit [20] = {0};

void H_LCD_void_Init(void)
{
	/*
#if (LCD_MODE == _8_BIT_MODE)

	//To Be Implemented*/
	/*
#elif (LCD_MODE == _4_BIT_MODE)
	 */
	DIO_voidSetPinDirection(pPORTA, LCD_RS_PIN, output);
	DIO_voidSetPinDirection(pPORTA, LCD_EN_PIN, output);
	_delay_ms(50);

	DIO_voidSetPinDirection(pPORTB, Pin0, output);
	DIO_voidSetPinDirection(pPORTB, pin1, output);
	DIO_voidSetPinDirection(pPORTB, pin2, output);
	DIO_voidSetPinDirection(pPORTB, pin4, output);
	//DIO_voidSetPortValue(pPORTB, 0x00);
	DIO_voidSetPinValue(pPORTA, LCD_EN_PIN, low);


	/* Initializing the LCD */
	H_LCD_void_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);
	H_LCD_void_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);
	H_LCD_void_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);
	H_LCD_void_sendCommand(LCD_CURSOR_ON);
	H_LCD_void_sendCommand(LCD_CLEAR);


	/*
 #endif*/

}
void H_LCD_void_sendData(u8 copy_u8data)
{
	DIO_voidSetPinValue(pPORTA, LCD_RS_PIN, high);
	_delay_ms(1);
	DIO_voidSetPinValue(pPORTA, LCD_EN_PIN, low);
	_delay_ms(1);
	H_LCD_void_latchByte(copy_u8data);
}
void H_LCD_void_sendCommand(u8 copy_u8command)
{
	DIO_voidSetPinValue(pPORTA, LCD_RS_PIN, low);
	_delay_ms(1);
	DIO_voidSetPinValue(pPORTA, LCD_EN_PIN, low);
	_delay_ms(1);
	H_LCD_void_latchByte(copy_u8command);
}
void H_LCD_void_sendString(const u8 * pstr)
{
	u8 i;
	while(pstr[i] != '\0')
	{
		H_LCD_void_sendData(pstr[i]);
		i++;
	}
}

void H_LCD_void_clearDisplay(void)
{
	DIO_voidSetPinValue(pPORTA, LCD_RS_PIN, low);
	_delay_ms(1);
	DIO_voidSetPinValue(pPORTA, LCD_EN_PIN, low);
	_delay_ms(1);
	H_LCD_void_latchByte(LCD_CLEAR);
}
void H_LCD_void_gotoXY(u8 copy_u8Row,u8 copy_u8Col)
{
	u8 location = 0;

	switch(copy_u8Row)
	{
	case 0:
		location = copy_u8Col;
		break;
	case 1:
		location = copy_u8Col + 0x40;
		break;
	case 2:
		location = copy_u8Col + 0x10;
		break;
	case 3:
		location = copy_u8Col + 0x50;
		break;
	}

	H_LCD_void_sendCommand((location | LCD_SET_CURSOR_LOCATION));
}

static void H_LCD_void_latchByte(u8 copy_u8Byte)
{

	DIO_voidSetPinValue(pPORTB, LCD_D7_PIN, (((copy_u8Byte)>>(7))&(0x01)));
	DIO_voidSetPinValue(pPORTB, LCD_D6_PIN, (((copy_u8Byte)>>(6))&(0x01)));
	DIO_voidSetPinValue(pPORTB, LCD_D5_PIN, (((copy_u8Byte)>>(5))&(0x01)));
	DIO_voidSetPinValue(pPORTB, LCD_D4_PIN, (((copy_u8Byte)>>(4))&(0x01)));

	/*
	u8 i=0,j=0;
	for(i = 7,j=3; i>=4 ; i--,j--)
	{
		DIO_voidSetPinValue(pPORTB, u8LCD_DataPins[j], ((copy_u8Byte>>i)&0x01));
	}
	 */
	DIO_voidSetPinValue(pPORTA, LCD_EN_PIN, high);
	_delay_ms(1);
	DIO_voidSetPinValue(pPORTA, LCD_EN_PIN, low);
	_delay_ms(5);
	/*
	for(i = 3,j=3; i>=0; i--,j--)
	{
		DIO_voidSetPinValue(pPORTB, u8LCD_DataPins[j], ((copy_u8Byte>>i)&0x01));
	}

	 */
	DIO_voidSetPinValue(pPORTB, LCD_D7_PIN, (((copy_u8Byte)>>(3))&(0x01)));
	DIO_voidSetPinValue(pPORTB, LCD_D6_PIN, (((copy_u8Byte)>>(2))&(0x01)));
	DIO_voidSetPinValue(pPORTB, LCD_D5_PIN, (((copy_u8Byte)>>(1))&(0x01)));
	DIO_voidSetPinValue(pPORTB, LCD_D4_PIN, (((copy_u8Byte)>>(0))&(0x01)));


	DIO_voidSetPinValue(pPORTA, LCD_EN_PIN, high);
	_delay_ms(1);
	DIO_voidSetPinValue(pPORTA, LCD_EN_PIN, low);
	_delay_ms(5);
}



void H_LCD_void_creatCustomChar(const u8 * ArrPattern,u8 copy_u8charLocation)
{
	unsigned char i;

	if(copy_u8charLocation < 8)
	{
		H_LCD_void_sendCommand(0X40 + (copy_u8charLocation*8));
		for(i=0 ; i<8 ; i++)
		{
			H_LCD_void_sendData(ArrPattern[i]);
		}
	}
	else
	{

	}
}
void H_LCD_void_displayCustomChar(u8 copy_u8charLocation)
{

	H_LCD_void_sendCommand(0X80 + copy_u8charLocation);
	H_LCD_void_sendData(copy_u8charLocation);

}

void H_LCD_void_displayHex(u8 copy_u8charCode)
{
	unsigned char val = 0;
	H_LCD_void_sendString("0x");

	val = ((0xF0 & copy_u8charCode)>>4);

	switch(val)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		H_LCD_void_sendData(val+'0');
		break;
	case 10:
		H_LCD_void_sendData('A');
		break;
	case 11:
		H_LCD_void_sendData('B');
		break;
	case 12:
		H_LCD_void_sendData('C');
		break;
	case 13:
		H_LCD_void_sendData('D');
		break;
	case 14:
		H_LCD_void_sendData('E');
		break;
	case 15:
		H_LCD_void_sendData('F');
		break;
	}

	val = (0x0F & copy_u8charCode);

	switch(val)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		H_LCD_void_sendData(val+'0');
		break;
	case 10:
		H_LCD_void_sendData('A');
		break;
	case 11:
		H_LCD_void_sendData('B');
		break;
	case 12:
		H_LCD_void_sendData('C');
		break;
	case 13:
		H_LCD_void_sendData('D');
		break;
	case 14:
		H_LCD_void_sendData('E');
		break;
	case 15:
		H_LCD_void_sendData('F');
		break;
	}
}
void H_LCD_void_displayBinary(u8 copy_u8charCode)
{
	unsigned char i;
	/* To be handled to send binary value for the character being input */
	/* print on screen "0b" create u8 digit and store the value of the 1st bit on the left using & with a mask 0x80 then shift the original value in a loop from 0-7 */
	H_LCD_void_sendString("0b");
	for(i=0;i<8;i++)
	{
		H_LCD_void_sendData(((copy_u8charCode>>(8-i-1))&0x01)+'0');
	}

}


void H_LCD_void_displayfloat(f32 copy_f32floatValue)
{
	 char i=0, dig=0;
	float val=copy_f32floatValue;

	// To be handled to send float value for the character being input
	// print the integer part first then the dot char then start to x10 for the float then get the % of it with 10 to print the values after the dot

	H_LCD_void_sendIntNum((int)copy_f32floatValue);
	H_LCD_void_sendData('.');
	if(val < 0)
	{
		val*=-1;
	}
	for(i=0;i<3;i++)
	{
		val *=10;
		dig = (unsigned char)(((long)val)%10);
		H_LCD_void_sendData(dig+'0');
	}
}

void H_LCD_void_sendIntNum(s32 copy_intNum)
{
	signed char digit[20]={0}, j, i = 0;
	int val = copy_intNum;

	if(val!= 0)
	{
		if(val < 0)
		{
			H_LCD_void_sendData('-');
			val *=-1;
		}
		while(val>=1)
		{
			i++;
			val /= 10;
		}
		val = copy_intNum;
		if(val < 1)
		{
			val *=-1;
		}
		for(j = (i-1); j>=0 ; j--) //489	i=3
		{
			digit[j] =  (char)((val%10)+'0');
			val /= 10;
		}
		H_LCD_void_sendString(digit);

	}
	else
	{
		H_LCD_void_sendData('0');
	}

	/*itoa(copy_s32Num,digit,10);*/
}
