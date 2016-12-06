/*
 * record.c
 *
 *  Created on: 2016年10月26日
 *      Author: redchenjs
 */
#include "../system/config.h"

extern uint8_t status_now;
extern uint8_t index_now;

extern uint16_t set_now;

void record_writeStatus(void)
{
	//-----写Flash前DCO时钟一定要重新确认一遍-----
    DCOCTL  = CALDCO_1MHZ;
    BCSCTL1 = CALBC1_1MHZ;

    Flash_Init(3,'B');																// 初始化Flash

	Flash_Bak_WriteChar(0x00, status_now);

	DCOCTL  = CALDCO_16MHZ;
	BCSCTL1 = CALBC1_16MHZ;
}

void record_writeLuxSet(void)
{
	//-----写Flash前DCO时钟一定要重新确认一遍-----
    DCOCTL  = CALDCO_1MHZ;
    BCSCTL1 = CALBC1_1MHZ;

    Flash_Init(3,'B');																// 初始化Flash

	Flash_Bak_WriteWord(0x02, set_now);

	DCOCTL  = CALDCO_16MHZ;
	BCSCTL1 = CALBC1_16MHZ;
}

void record_writeAll(void)
{
	//-----写Flash前DCO时钟一定要重新确认一遍-----
    DCOCTL  = CALDCO_1MHZ;
    BCSCTL1 = CALBC1_1MHZ;

    Flash_Init(3,'B');																// 初始化Flash
	Flash_Erase();																	// 擦除Info_B

	Flash_Direct_WriteChar(0x00, status_now);
	Flash_Direct_WriteWord(0x02, set_now);

	DCOCTL  = CALDCO_16MHZ;
	BCSCTL1 = CALBC1_16MHZ;
}

void record_readAll(void)
{
	//-----写Flash前DCO时钟一定要重新确认一遍-----
    DCOCTL  = CALDCO_1MHZ;
    BCSCTL1 = CALBC1_1MHZ;

    Flash_Init(3,'B');																// 初始化Flash

    status_now = Flash_ReadChar(0x00);
    set_now    = Flash_ReadWord(0x02);

    if (status_now > 3) status_now = 0;

    if (!status_now)
    	index_now = 0;
    else
    	index_now = 15;

	DCOCTL  = CALDCO_16MHZ;
	BCSCTL1 = CALBC1_16MHZ;
}
