/*
 * app.c
 *
 *  Created on: Nov 5, 2023
 *      Author: Ebram Habib
 */
#include "std_types.h"
#include "GIE_int.h"
#include "LCD_int.h"
#include "GPIO_Int.h"
#include "ULTRASONIC_int.h"
#include "KeyPad.h"
#include "TIMER1_int.h"
#include "TIMER0_int.h"

/* Global Variables */

TIMER0_INIT_CONFIG config = {
		TIMER0_COMPARE_OUTPUT_NON_PWM_MODE_OC0_DISCONNECTED,
		TIMER0_COMPARE_OUTPUT_FAST_PWM_MODE_OC0_CLEAR,
		TIMER0_COMPARE_OUTPUT_PHASE_CORRECT_PWM_MODE_OC0_DISCONNECTED,
		TIMER0_FCPU_DIVIDED_BY_1024,
		TIMER0_NORMAL_MODE,
		0,
		0 };

typedef enum{
	MONITOR_DISTANCE, GET_PASSWORD, CHECK_PASSWORD, SYSTEM_BLOCKED, LOGIN_SUCCESSFUL, LED_CONTROL, SYSTEM_LOGOUT
}STATE_MACHINE;

STATE_MACHINE runTask = MONITOR_DISTANCE;

u8 flag = 0;
u16 pass = 1234, newPass=0; /* pass >> preset password, newPass >> new password from the user */

/* Function Prototypes */
void APP_delayCallBack(void);
void APP_delay(u32 millisec);
void APP_monitorDistance(void);
void APP_getPassword(void);
void APP_checkPassword(void);
void APP_systemBlocked(void);
void APP_loginSuccessful(void);
void APP_controlLEDs(void);
void APP_systemLogout(void);


int main()
{

	/* Set relay pin as output */
	DIO_voidSetPinDirection(pPORTC, pin7, output);
	DIO_voidSetPinValue(pPORTC, pin7, LOGIC_LOW);

	/* LEDs Initialization */
	DIO_voidSetPinDirection(pPORTA, pin4, output); /* Green LED */
	DIO_voidSetPinDirection(pPORTA, pin5, output); /* Blue LED */
	DIO_voidSetPinDirection(pPORTB, pin7, output); /* RED LED */

	/* Default state of LEDs is OFF */
	DIO_voidSetPinValue(pPORTA, pin4, LOGIC_LOW);
	DIO_voidSetPinValue(pPORTA, pin5, LOGIC_LOW);
	DIO_voidSetPinValue(pPORTB, pin7, LOGIC_LOW);

	/* Component Initialization */
	H_LCD_void_Init();
	Timer0_Init(&config);
	Ultrasonic_init();
	KEYPAD_Init();
	GIE_Enable();

	while(1)
	{
		/* Applying state machine mechanism */
		switch(runTask)
		{
		case MONITOR_DISTANCE:
			APP_monitorDistance();
			break;
		case GET_PASSWORD:
			APP_getPassword();
			break;
		case CHECK_PASSWORD:
			APP_checkPassword();
			break;
		case SYSTEM_BLOCKED:
			APP_systemBlocked();
			break;
		case LOGIN_SUCCESSFUL:
			APP_loginSuccessful();
			break;
		case LED_CONTROL:
			APP_controlLEDs();
			break;
		case SYSTEM_LOGOUT:
			APP_systemLogout();
			break;
		}
	}
}
/* Call Back Function for Timer0 */
void APP_delayCallBack(void)
{
	flag = 1;
}
/* Generic function to set delay in ms */
void APP_delay(u32 millisec)
{
	Timer0_SetCallBack(APP_delayCallBack);
	TIMER0_clearTimerValue();
	Timer0_SetDelayTimeMilliSec(&config, millisec);
	while(flag == 0);	/* wait till flag is set */
	flag = 0;			/* clear flag */
}

void APP_monitorDistance(void)
{
	u16 distance = 0;

	H_LCD_void_clearDisplay();
	H_LCD_void_gotoXY(0, 0);
	H_LCD_void_sendString("Distance=     cm");
	do
	{
		distance = Ultrasonic_readDistance();
		/* Reading a 2nd time to ensure it's not just noise */
		APP_delay(1);
		distance = Ultrasonic_readDistance();

		if(distance >= 100)
		{
			H_LCD_void_gotoXY(0, 10);
			H_LCD_void_sendIntNum(distance);
		}
		else if(distance < 100)	/* If the distance falls back under 100 write over the 3rd digit with ' ' */
		{
			H_LCD_void_gotoXY(0, 10);
			H_LCD_void_sendIntNum(distance);
			H_LCD_void_sendData(' ');
		}
	}while(distance > 15); /* when a user is detected deactivate ultrasonic sensor */

	Ultrasonic_disable();
	H_LCD_void_clearDisplay();
	H_LCD_void_gotoXY(0, 0);
	H_LCD_void_sendString("Hello ...");
	APP_delay(1000);
	runTask = GET_PASSWORD;		/* state switching */
}
void APP_getPassword(void)
{
	u8 i, digit;

	H_LCD_void_clearDisplay();
	H_LCD_void_gotoXY(0, 0);
	H_LCD_void_sendString("Please Enter Pass:");
	H_LCD_void_gotoXY(1, 0);
	newPass = 0;			/* flushing out any old passwords from the buffer */
	for(i=0 ; i<4 ; i++)
	{
		digit = KEYPAD_Get_Pressed_Key();
		H_LCD_void_sendData(digit+'0');
		newPass = ((newPass*10) + digit);
		APP_delay(250);
	}
	APP_delay(500);
	runTask = CHECK_PASSWORD;	/* state switching */
}
void APP_checkPassword(void)
{
	static u8 trials = 3;

	if(newPass != pass)
	{
		H_LCD_void_clearDisplay();
		H_LCD_void_gotoXY(0, 0);
		H_LCD_void_sendString("Incorrect Pass");
		APP_delay(500);
		trials--;

		if(trials == 0)
		{
			runTask = SYSTEM_BLOCKED;	/* state switching */
			trials = 3;
		}
		else
		{
			H_LCD_void_gotoXY(1, 0);
			H_LCD_void_sendString("Plz try again: ");
			APP_delay(500);
			runTask = GET_PASSWORD;		/* state switching */
		}
	}
	else if(newPass == pass)
	{
		runTask = LOGIN_SUCCESSFUL;		/* state switching */
		trials = 3;
	}
}
void APP_systemBlocked(void)
{
	H_LCD_void_clearDisplay();
	H_LCD_void_gotoXY(0, 0);
	H_LCD_void_sendString("System Blocked");
	H_LCD_void_gotoXY(1, 0);
	H_LCD_void_sendString("For 2min");
	APP_delay(5000);
	Ultrasonic_enable();
	runTask = MONITOR_DISTANCE;			/* state switching */
}
void APP_loginSuccessful(void)
{
	H_LCD_void_clearDisplay();
	H_LCD_void_gotoXY(0, 0);
	H_LCD_void_sendString("Welcome Ebram!");
	/* Open Relay */
	DIO_voidSetPinValue(pPORTC, pin7, LOGIC_HIGH);
	APP_delay(1000);
	runTask = LED_CONTROL;			/* state switching */
}
void APP_controlLEDs(void)
{
	u8 digit = 0;

	H_LCD_void_clearDisplay();
	H_LCD_void_gotoXY(0, 0);
	H_LCD_void_sendString("LEDs Status:");
	H_LCD_void_gotoXY(1, 0);
	H_LCD_void_sendString("1- On");
	H_LCD_void_gotoXY(1, 8);
	H_LCD_void_sendString("2- Off");
	do{
		digit = KEYPAD_Get_Pressed_Key();
	}while((digit != 1)&&(digit != 2));
	if(digit == 1)
	{
		H_LCD_void_clearDisplay();
		H_LCD_void_gotoXY(0, 0);
		H_LCD_void_sendString("LEDs are On");
		DIO_voidSetPinValue(pPORTA, pin4, LOGIC_HIGH);
		DIO_voidSetPinValue(pPORTA, pin5, LOGIC_HIGH);
		DIO_voidSetPinValue(pPORTB, pin7, LOGIC_HIGH);

	}
	else if(digit == 2)
	{
		H_LCD_void_clearDisplay();
		H_LCD_void_gotoXY(0, 0);
		H_LCD_void_sendString("LEDs are Off");
		DIO_voidSetPinValue(pPORTA, pin4, LOGIC_LOW);
		DIO_voidSetPinValue(pPORTA, pin5, LOGIC_LOW);
		DIO_voidSetPinValue(pPORTB, pin7, LOGIC_LOW);
	}
	APP_delay(1000);

	runTask = SYSTEM_LOGOUT;			/* state switching */
}

void APP_systemLogout(void)
{
	u8 digit = 0;

	H_LCD_void_clearDisplay();
	H_LCD_void_gotoXY(0, 0);
	H_LCD_void_sendString("To Logout");
	H_LCD_void_gotoXY(1, 6);
	H_LCD_void_sendString("Press 1");
	do{
		digit = KEYPAD_Get_Pressed_Key();
	}
	while(digit != 1);
	H_LCD_void_clearDisplay();
	H_LCD_void_gotoXY(0, 0);
	H_LCD_void_sendString("System Locked");
	H_LCD_void_gotoXY(1, 0);
	H_LCD_void_sendString("GoodBye...");
	APP_delay(1000);
	/* Close Relay */
	DIO_voidSetPinValue(pPORTC, pin7, LOGIC_LOW);

	runTask = MONITOR_DISTANCE;		/* state switching */
	Ultrasonic_enable();	/* Re-enable the ultrasonic before going back to the monitor distance state */
}
