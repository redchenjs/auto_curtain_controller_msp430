/*
 * wdt.c
 *
 *  Created on: 2016-10-20
 *      Author: Jack Chen <redchenjs@live.com>
 */

#include <msp430.h>

void wdt_init(void)
{
    WDTCTL = WDT_MDLY_8;
    IE1 |= WDTIE;
}
