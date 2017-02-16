/*
 * record.c
 *
 *  Created on: 2016年10月26日
 *      Author: redchenjs
 */
#include <msp430g2553.h>
#include "../device/flash.h"

extern unsigned char status_now;
extern unsigned char index_now;

extern unsigned int set_now;

void record_write_status(void)
{
	//-----写Flash前DCO时钟一定要重新确认一遍-----
    DCOCTL  = CALDCO_1MHZ;
    BCSCTL1 = CALBC1_1MHZ;

    flash_init(3,'B');																// 初始化Flash

	flash_bak_write_char(0x00, status_now);

	DCOCTL  = CALDCO_16MHZ;
	BCSCTL1 = CALBC1_16MHZ;
}

void record_write_settings(void)
{
	//-----写Flash前DCO时钟一定要重新确认一遍-----
    DCOCTL  = CALDCO_1MHZ;
    BCSCTL1 = CALBC1_1MHZ;

    flash_init(3,'B');																// 初始化Flash

	flash_bak_write_word(0x02, set_now);

	DCOCTL  = CALDCO_16MHZ;
	BCSCTL1 = CALBC1_16MHZ;
}

void record_write_all(void)
{
	//-----写Flash前DCO时钟一定要重新确认一遍-----
    DCOCTL  = CALDCO_1MHZ;
    BCSCTL1 = CALBC1_1MHZ;

    flash_init(3,'B');																// 初始化Flash
	flash_erase();																	// 擦除Info_B

	flash_direct_write_char(0x00, status_now);
	flash_direct_write_word(0x02, set_now);

	DCOCTL  = CALDCO_16MHZ;
	BCSCTL1 = CALBC1_16MHZ;
}

void record_read_all(void)
{
	//-----写Flash前DCO时钟一定要重新确认一遍-----
    DCOCTL  = CALDCO_1MHZ;
    BCSCTL1 = CALBC1_1MHZ;

    flash_init(3,'B');																// 初始化Flash

    status_now = flash_read_char(0x00);
    set_now    = flash_read_word(0x02);

    if (status_now > 3) status_now = 0;

    if (!status_now)
    	index_now = 0;
    else
    	index_now = 15;

	DCOCTL  = CALDCO_16MHZ;
	BCSCTL1 = CALBC1_16MHZ;
}
