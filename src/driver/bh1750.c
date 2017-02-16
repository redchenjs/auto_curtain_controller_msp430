#include "../device/delay.h"
#include "../interface/i2c.h"
/*
 * BH1750.cpp
 *
 *  Created on: 2016年10月20日
 *      Author: redchenjs
 */
#define BH1750_ADDRESS 0x23
#define ONE_TIME_H_RESOLUTION_MODE 0x20
//One Time H-Resolution Mode:
//Resolution = 1 lux
//Measurement time (max.) = 180ms
//Power down after each measurement

unsigned int bh1750_get_lux(void)
{
	unsigned char temp[2];

    i2c_transmit_frame(BH1750_ADDRESS, "\x20", 1);

    delay_ms(180);

    i2c_receive_frame(BH1750_ADDRESS, temp, 2);

    return (unsigned int)(temp[0]<<8) | temp[1];
}

void bh1750_init(void)
{

}
