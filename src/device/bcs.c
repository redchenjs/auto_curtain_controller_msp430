/*
 * bcs.c
 *
 *  Created on: 2016-03-22
 *      Author: Jack Chen <redchenjs@live.com>
 */

#include <msp430.h>

void bcs_init(void)
{
    DCOCTL  = CALDCO_16MHZ;
    BCSCTL1 = CALBC1_16MHZ;
}
