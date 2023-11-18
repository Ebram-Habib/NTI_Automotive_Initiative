/*
 * WiFi_prog.c
 *
 *  Created on: Nov 16, 2023
 *      Author: Ebram Habib
 */
#include "std_types.h"
#include "TIMER0_int.h"
#include "UART_int.h"
#include "WiFi_int.h"

/* Global variables */
/* flag to be used for delays */
u8 flag=0;
/* Initialize the timer for delays in the normal mode */
TIMER0_INIT_CONFIG config = {
		TIMER0_COMPARE_OUTPUT_NON_PWM_MODE_OC0_DISCONNECTED,
		TIMER0_COMPARE_OUTPUT_FAST_PWM_MODE_OC0_CLEAR,
		TIMER0_COMPARE_OUTPUT_PHASE_CORRECT_PWM_MODE_OC0_DISCONNECTED,
		TIMER0_FCPU_DIVIDED_BY_1024,
		TIMER0_NORMAL_MODE,
		0,
		0 };

/* Function Definitions */

/* Initialize the Wifi module */
u8 WIFI_init(void)
{
	UART_init();
	UART_sendString("ATE0\r\n");
	UART_sendString("AT+CWMODE=3\r\n");
}

/* Connect to network */
u8 WIFI_connectRouter(void)
{
	UART_sendString("AT+CWJAP=\"HUAWEI Y9 2018\",\"1111ieee\"\r\n");
}

/* Connect to phone */
u8 WIFI_connectPhone(void)
{
	UART_sendString("AT+CIPSTART=\"TCP\",\"192.168.43.1\",4000\r\n");
}

/* Receive byte from the WiFi module through uart */
u8 WIFI_receiveData(u8* data)
{
	UART_recieveByteSynchNonBlocking(data);
}

/* Delay callback function */
void WIFI_delayCallBack(void)
{
	flag = 1;
}

/* Delay function */
void WIFI_delayMilliSec(u32 millisec)
{

	Timer0_SetCallBack(WIFI_delayCallBack);
	TIMER0_clearTimerValue();
	Timer0_SetDelayTimeMilliSec(&config,millisec);
	while(flag == 0);
	flag = 0;
}
