#include <msp430g2553.h>
#include "../user/motor.h"
#include "../user/record.h"
#include "../user/display.h"
#include "../driver/bh1750.h"
/*
 * senser.c
 *
 *  Created on: 2016年10月20日
 *      Author: redchenjs
 */
unsigned int senser_lux_now  = 0x0000;
unsigned int senser_lux_past = 0xffff;

unsigned int senser_set_now  = 0x0000;
unsigned int senser_set_past = 0xffff;

void senser_get_lux(void)
{
	static unsigned int cnt_above = 0;
	static unsigned int cnt_below = 0;

	senser_lux_now = bh1750_get_lux();
	bh1750_set_mode(BH1750_ONE_TIME_H_RESOLUTION_MODE);

	if (senser_lux_now >= senser_set_now) {
		cnt_above++;
	}
	else {
		cnt_below++;
	}

	if (cnt_above >= 1) {
		cnt_above = 0;
		if (display_index_now < 15) {
			display_index_now++;
		}
	}

	if (cnt_below >= 1) {
		cnt_below = 0;
		if (display_index_now > 0) {
			display_index_now--;
		}
	}

	if (display_index_now == 15 && motor_status_now != 1){
		motor_status_now = 3;
	}

	if (display_index_now == 0 && motor_status_now != 0){
		motor_status_now = 2;
	}
}

void senser_set_lux(unsigned int now)
{
	senser_set_now = now;

	record_write_settings();
}
