#include <msp430.h>
/*
 * wdt.c
 *
 *  Created on: 2016-10-20
 *      Author: redchenjs
 */

void wdt_init(void)
{
	WDTCTL = WDT_MDLY_8;
	IE1	|= WDTIE;
}
