/*
 * main.c
 *
 *  Created on: Oct 23, 2023
 *      Author: Ebram Habib
 */

#include "LCD_int.h"
#include "KeyPad.h"
#include <avr/delay.h>

typedef struct{
	u16 ID;
	u16 Password;
	u8 Name[15];
}DATA_BASE;

u8 nameInArabic[5][8] = {
		{0x0,0x03,0x0F,0x08,0x08,0x08,0x08,0x0},
		{0x00,0x04,0x04,0x04,0x04,0x04,0x04,0x00},
		{0x00,0x00,0x00,0x01,0x01,0x02,0x1C,0x00},
		{0x00,0x00,0x04,0x1C,0x08,0x00,0x00,0x00},
		{0x08,0x08,0x08,0x08,0x08,0x00,0x0C,0x18}
};

u8 smilelyFace[8] = {0x0,0x0,0x0A,0x0,0x11,0x0E,0x0,0x0};

DATA_BASE D1 = {
		1234,5060, "Ebram Edward"
};

DATA_BASE D2 = {
		5678,1020, "Sara Omar"
};


u8 dataBaseCheck(void);

int main()
{

	KEYPAD_Init();
	H_LCD_void_Init();

	dataBaseCheck();




	while(1)
	{


	}

}

u8 dataBaseCheck(void)
{
	u8 i,digit = 0;
	u16 pass = 0, id = 0;


	H_LCD_void_sendString("Please Enter ID:");
	H_LCD_void_gotoXY(1, 0);
	for(i=0 ; i<4 ; i++)
	{
		digit = KEYPAD_Get_Pressed_Key();
		H_LCD_void_sendData(digit+'0');
		id = ((id*10) + digit);
		_delay_ms(500);
	}

	if((id == D1.ID)|| (id == D2.ID))
	{
		H_LCD_void_clearDisplay();
		H_LCD_void_gotoXY(0, 0);
		H_LCD_void_sendString("Please Enter Pass:");
		H_LCD_void_gotoXY(1, 0);
		for(i=0 ; i<4 ; i++)
		{
			digit = KEYPAD_Get_Pressed_Key();
			H_LCD_void_sendData(digit+'0');
			pass = ((pass*10) + digit);
			_delay_ms(500);
		}
	}
	else
	{
		H_LCD_void_clearDisplay();
		H_LCD_void_gotoXY(0, 0);
		H_LCD_void_sendString("Wrong ID");
		_delay_ms(1000);
		return 0;
	}
	if((id == D1.ID )&&(pass == D1.Password))
	{
		H_LCD_void_clearDisplay();
		H_LCD_void_gotoXY(0, 0);
		H_LCD_void_sendString("Welcome, ");
		//H_LCD_void_gotoXY(1, 0);
		H_LCD_void_creatCustomChar(smilelyFace, 8);
		H_LCD_void_displayCustomChar(8);
		H_LCD_void_sendData(' ');
		for(i=0;i<5;i++)
		{
			H_LCD_void_creatCustomChar(nameInArabic[i], i+10);
			H_LCD_void_displayCustomChar(i+10);
		}
		_delay_ms(10000);
		//H_LCD_void_clearDisplay();
		H_LCD_void_gotoXY(0, 0);
		return 1;
	}

	else if((id == D2.ID )&&(pass == D2.Password))
	{
		H_LCD_void_clearDisplay();
		H_LCD_void_gotoXY(0, 0);
		H_LCD_void_sendString("Welcome, Sara!");
		_delay_ms(1000);
		H_LCD_void_clearDisplay();
		H_LCD_void_gotoXY(0, 0);
		return 1;
	}
	else
	{
		H_LCD_void_clearDisplay();
		H_LCD_void_gotoXY(0, 0);
		H_LCD_void_sendString("Wrong password");
		_delay_ms(1000);
		H_LCD_void_clearDisplay();
		H_LCD_void_gotoXY(0, 0);
		return 0;
	}
}
