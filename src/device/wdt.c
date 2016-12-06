/*
 * wdt.c
 *
 *  Created on: 2016年10月20日
 *      Author: redchenjs
 */
#include "wdt.h"

void wdt_init(void)
{
	WDTCTL = WDT_ADLY_1000;
	IE1	|= WDTIE;
}

#pragma vector=WDT_VECTOR
__interrupt void WDT_ISR(void)
{
	__bic_SR_register_on_exit(LPM3_bits + GIE);
}
