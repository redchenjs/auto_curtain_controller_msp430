#include <msp430.h>
/*
 * wdt.c
 *
 *  Created on: 2016年10月20日
 *      Author: redchenjs
 */

void wdt_init(void)
{
	WDTCTL = WDT_MDLY_8;
	IE1	|= WDTIE;
}

#pragma vector=WDT_VECTOR
__interrupt void WDT_ISR(void)
{
	static unsigned int cnt = 0;

	if (cnt++ > 400) {
		cnt = 0;
		__bic_SR_register_on_exit(LPM0_bits);
	}
}
