/*
 * bh1750.c
 *
 *  Created on: 2016-10-20
 *      Author: Jack Chen <redchenjs@live.com>
 */

#include "chip/i2c.h"

#include "board/bh1750.h"

#define BH1750_ADDRESS 0x23

unsigned int bh1750_get_lux(void)
{
    unsigned char temp[2];

    i2c_receive_frame(BH1750_ADDRESS, temp, 2);

    return (unsigned int)(temp[0]<<8) | temp[1];
}

void bh1750_set_mode(unsigned char mode)
{
    i2c_transmit_frame(BH1750_ADDRESS, &mode, 1);
}

void bh1750_init(void)
{
    bh1750_set_mode(ONE_TIME_H_RESOLUTION_MODE);
}
