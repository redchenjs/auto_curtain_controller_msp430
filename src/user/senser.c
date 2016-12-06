/*
 * senser.c
 *
 *  Created on: 2016年10月20日
 *      Author: redchenjs
 */
#include "senser.h"

BH1750 Senser;

uint16_t lux_now  = 0x0000;
uint16_t lux_past = 0xffff;

uint16_t set_now  = 0x0000;
uint16_t set_past = 0xffff;

uint8_t index_now  = 0x00;
uint8_t index_past = 0xff;

extern uint8_t status_now;

void senser_getLux(void)
{
	static uint16_t cnt_above = 0;
	static uint16_t cnt_below = 0;

	Senser.getLux(lux_now);

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

void senser_setLux(uint16_t now)
{
	set_now = now;

	record_writeLuxSet();
}
