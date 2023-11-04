/*
 * RTC_int.h
 *
 *  Created on: Nov 3, 2023
 *      Author: Ebram Habib
 */

#ifndef RTC_INT_H_
#define RTC_INT_H_

typedef struct{
	u8 seconds;
	u8 minuets;
	u8 hours;
	enum{
		AM,PM,
	}AMPM_MODE;
	enum{
			TWELVE_HOURS,TWENTYFOUD_HOURS,
		}HOURS_MODE;
}RTC_TIME;

typedef struct{
	enum{
				SATURDAY,SUNDAY,MONDAY,TUESDAY,WEDNESDAY,THURSDAY,FRIDAY
			}DAY;
	u8 date;
	u8 month;
	u8 year;
}RTC_DATE;

void RTC_init(void);
u8 RTC_setTime(RTC_TIME* time_config_ptr);
u8 RTC_getTime(RTC_TIME* time_config_ptr);
u8 RTC_setDate(RTC_DATE* date_config_ptr);
u8 RTC_getDate(RTC_DATE* date_config_ptr);

#endif /* RTC_INT_H_ */
