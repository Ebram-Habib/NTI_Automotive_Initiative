/*
 * main.c
 *
 *  Created on: Nov 3, 2023
 *      Author: Ebram Habib
 */

#include "std_types.h"
#include "RTC_int.h"
#include <avr/delay.h>

RTC_TIME time = {
		55,
		59,
		19,
		AM,
		TWENTYFOUD_HOURS
};

RTC_DATE date = {
		FRIDAY,
		15,
		7,
		19
};
/* don't forget to leave a 1ms delay between each func */

int main()
{

	RTC_init();

	RTC_setTime(&time);
	_delay_ms(1);
	RTC_setDate(&date);
	while(1)
	{

	}
}
