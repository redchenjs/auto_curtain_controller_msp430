/*
 * user.c
 *
 *  Created on: 2016年10月21日
 *      Author: redchenjs
 */
#include "config.h"

void user_init(void)
{
	record_readAll();

	senser_setLux(100);

	display_init();

}

void user_loop(void)
{
	senser_getLux();

	display_refreshLux();
	display_refreshSet();
	display_refreshStatus();
	display_refreshProgress();

	motor_set();
}


