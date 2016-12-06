/*
 * clock.c
 *
 *  Created on: 2016年10月20日
 *      Author: redchenjs
 */
#include "clock.h"

DS3231 Clock;
byte year, month, date, DoW, hour, minute, second;

void clock_getTime(void)
{
	Clock.getTime(year, month, date, DoW, hour, minute, second);
}
