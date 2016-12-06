/*
 * BCSplus_init.c
 *
 *  Created on: 2016-3-22
 *      Author: redchenjs
 */
#include "../system/config.h"

void bcs_init(void)
{
	DCOCTL  = CALDCO_16MHZ;
	BCSCTL1 = CALBC1_16MHZ;
}

