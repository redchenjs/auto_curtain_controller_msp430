#include "user/motor.h"
#include "user/record.h"
#include "user/display.h"
#include "driver/bh1750.h"
/*
 * senser.c
 *
 *  Created on: 2016-10-20
 *      Author: redchenjs
 */

unsigned int senser_lux_now  = 0x0000;
unsigned int senser_lux_past = 0x0000;

unsigned int senser_set_now  = 0x0000;
unsigned int senser_set_past = 0x0000;

void senser_update(void)
{
	senser_lux_now = bh1750_get_lux();
	bh1750_set_mode(ONE_TIME_H_RESOLUTION_MODE);
}

void senser_set_lux(unsigned int value)
{
    senser_set_past = senser_set_now;
    senser_set_now = value;

	record_write_all();
}
