/*
 * bluetooth.c
 *
 *  Created on: 2017-03-09
 *      Author: Jack Chen <redchenjs@live.com>
 */

#include <msp430.h>

#include "board/bluetooth.h"

unsigned int blu_link_status = OFFLINE;

void blu_refresh(void)
{
    if (P1IN & BIT3) {
        blu_link_status = ONLINE;
    } else {
        blu_link_status = OFFLINE;
    }
}

void blu_init(void)
{
    P1DIR &=~BIT3;      // 设置为输入口
    P1REN |= BIT3;      // 启用上下拉电阻
    P1OUT &= BIT3;      // 启用下拉

    blu_refresh();
}
