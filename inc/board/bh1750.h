/*
 * bh1750.h
 *
 *  Created on: 2016-10-20
 *      Author: Jack Chen <redchenjs@live.com>
 */

#ifndef INC_BOARD_BH1750_H
#define INC_BOARD_BH1750_H

enum bh1750_mode_table {
    ONE_TIME_H_RESOLUTION_MODE = 0x20
};
// One Time H-Resolution Mode:
// Resolution = 1 lux
// Measurement time (max.) = 180ms
// Power down after each measurement

extern unsigned int bh1750_get_lux(void);
extern void bh1750_set_mode(unsigned char mode);
extern void bh1750_init(void);

#endif /* INC_BOARD_BH1750_H */
