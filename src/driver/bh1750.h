/*
 * bh1750.h
 *
 *  Created on: 2016年10月20日
 *      Author: redchenjs
 */
#ifndef BH1750_H
#define BH1750_H

#define BH1750_ADDRESS 0x23
#define BH1750_ONE_TIME_H_RESOLUTION_MODE 0x20
//One Time H-Resolution Mode:
//Resolution = 1 lux
//Measurement time (max.) = 180ms
//Power down after each measurement

extern unsigned int bh1750_get_lux(void);
extern void bh1750_set_mode(unsigned char mode);
extern void bh1750_init(void);

#endif

