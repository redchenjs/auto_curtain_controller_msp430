/*
 * wdt.c
 *
 *  Created on: 2016年10月20日
 *      Author: redchenjs
 */
#include "msp430g2553.h"

void wdt_init(void)
{
	WDTCTL = WDT_MDLY_32;
	IE1	|= WDTIE;
}

#pragma vector=WDT_VECTOR
__interrupt void WDT_ISR(void)
{
	static int cnt = 0;

	if (cnt++ > 180) {
		cnt = 0;
		__bic_SR_register_on_exit(LPM3_bits + GIE);
	}
}
