/*
 * main.c
 *
 *  Created on: Nov 4, 2023
 *      Author: Ebram Habib
 */

#include "std_types.h"
#include "FingerPS_int.h"
#include "UART_int.h"
#include "GIE_int.h"
#include "GPIO_Int.h"
#include "LCD_int.h"
#include "KeyPad.h"

extern u8 UsersCounter;

u8 APP_Enroll(void);
u8 APP_Login(void);

int main()
{
	u8 choice = 0;

	KEYPAD_Init();
	H_LCD_void_Init();
	FingerPS_init();
	GIE_Enable();


	while(1)
	{
		H_LCD_void_clearDisplay();
		H_LCD_void_sendString("Plz Choose Mode:");
		H_LCD_void_gotoXY(1, 0);
		H_LCD_void_sendString("1- Enroll   2- Login");
		choice = KEYPAD_Get_Pressed_Key();

		switch(choice)
		{
		case 1:
			APP_Enroll();
			break;
		case 2:
			APP_Login();
			break;
		}

	}
}

u8 APP_Enroll(void)
{
	if(FingerPS_handShake() == ERROR)
	{
		H_LCD_void_clearDisplay();
		H_LCD_void_sendString("Error, plz try again");
		delayMilliSec(1000);
		return ERROR;
	}
	else
	{
		if(FingerPS_genImg() == ERROR)
		{
			H_LCD_void_clearDisplay();
			H_LCD_void_sendString("Error, plz try again");
			delayMilliSec(1000);
			return ERROR;
		}
		else
		{
			if(FingerPS_convertImg2CharFile(CHARACTERFILE1) == ERROR)
			{
				H_LCD_void_clearDisplay();
				H_LCD_void_sendString("Error, plz try again");
				delayMilliSec(1000);
				return ERROR;
			}
			else
			{
				if(FingerPS_genImg() == ERROR)
				{
					H_LCD_void_clearDisplay();
					H_LCD_void_sendString("Error, plz try again");
					delayMilliSec(1000);
					return ERROR;
				}
				else
				{
					if(FingerPS_convertImg2CharFile(CHARACTERFILE2) == ERROR)
					{
						H_LCD_void_clearDisplay();
						H_LCD_void_sendString("Error, plz try again");
						delayMilliSec(1000);
						return ERROR;
					}
					else
					{
						if(FingerPS_genTemplate() == ERROR)
						{
							H_LCD_void_clearDisplay();
							H_LCD_void_sendString("Error, plz try again");
							delayMilliSec(1000);
							return ERROR;
						}
						else
						{
							if(FingerPS_strTemplate(UsersCounter) == ERROR)
							{
								H_LCD_void_clearDisplay();
								H_LCD_void_sendString("Error, plz try again");
								delayMilliSec(1000);
								return ERROR;
							}
							else
							{
								/* Display "Enrolled" on LCD */
								H_LCD_void_clearDisplay();
								H_LCD_void_sendString("Enroll Successful");
								delayMilliSec(1000);
								return SUCCESS;

							}
						}
					}
				}
			}
		}

	}

}

u8 APP_Login(void)
{
	if(FingerPS_genImg() == ERROR)
	{
		H_LCD_void_clearDisplay();
		H_LCD_void_sendString("Error, plz try again");
		delayMilliSec(1000);
		return ERROR;
	}
	else
	{
		if(FingerPS_convertImg2CharFile(CHARACTERFILE1) == ERROR)
		{
			H_LCD_void_clearDisplay();
			H_LCD_void_sendString("Error, plz try again");
			delayMilliSec(1000);
			return ERROR;
		}
		else
		{
			if(FingerPS_searchFinger() == ERROR)
			{
				H_LCD_void_clearDisplay();
				H_LCD_void_sendString("User Not Found");
				delayMilliSec(1000);
				return ERROR;
			}
			else
			{
				/* user found */
				H_LCD_void_clearDisplay();
				H_LCD_void_sendString("Login Successful");
				delayMilliSec(1000);
				return SUCCESS;
			}
		}
	}
}
