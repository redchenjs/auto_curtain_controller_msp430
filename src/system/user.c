#include "user/motor.h"
#include "user/senser.h"
#include "user/record.h"
#include "user/display.h"
#include "interface/i2c.h"
/*
 * user.c
 *
 *  Created on: 2016年10月21日
 *      Author: redchenjs
 */

void user_init(void)
{
	record_read_all();

	senser_set_lux(100);

	display_init();

}

void user_loop(void)
{
	senser_get_lux();

	display_refresh_lux();
	display_refresh_set();
	display_refresh_status();
	display_refresh_progress();

	motor_update();
}


