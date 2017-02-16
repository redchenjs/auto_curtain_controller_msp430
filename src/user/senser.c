/*
 * senser.c
 *
 *  Created on: 2016年10月20日
 *      Author: redchenjs
 */
#include <msp430g2553.h>
#include "../user/record.h"
#include "../driver/bh1750.h"

unsigned int lux_now  = 0x0000;
unsigned int lux_past = 0xffff;

unsigned int set_now  = 0x0000;
unsigned int set_past = 0xffff;

unsigned char index_now  = 0x00;
unsigned char index_past = 0xff;

extern unsigned char status_now;

void senser_get_lux(void)
{
	static unsigned int cnt_above = 0;
	static unsigned int cnt_below = 0;

	lux_now = bh1750_get_lux();

	if (lux_now >= set_now) {
		cnt_above++;
	}
	else {
		cnt_below++;
	}

	if (cnt_above >= 1) {
		cnt_above = 0;
		if (index_now < 15) {
			index_now++;
		}
	}

	if (cnt_below >= 1) {
		cnt_below = 0;
		if (index_now > 0) {
			index_now--;
		}
	}

	if (index_now == 15 && status_now != 1){
		status_now = 3;
	}

	if (index_now == 0 && status_now != 0){
		status_now = 2;
	}
}

void senser_set_lux(unsigned int now)
{
	set_now = now;

	record_write_settings();
}
