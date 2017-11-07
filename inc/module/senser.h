/*
 * senser.h
 *
 *  Created on: 2016-10-20
 *      Author: redchenjs
 */

#ifndef SENSER_H_
#define SENSER_H_

extern unsigned int senser_lux_now;
extern unsigned int senser_lux_past;

extern unsigned int senser_set_now;
extern unsigned int senser_set_past;

extern void senser_update(void);
extern void senser_set_lux(unsigned int now);

#endif
