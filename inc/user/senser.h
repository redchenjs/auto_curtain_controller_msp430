/*
 * senser.h
 *
 *  Created on: 2016-10-20
 *      Author: Jack Chen <redchenjs@live.com>
 */

#ifndef INC_USER_SENSER_H_
#define INC_USER_SENSER_H_

extern unsigned int senser_lux_now;
extern unsigned int senser_lux_past;

extern unsigned int senser_set_now;
extern unsigned int senser_set_past;

extern void senser_update(void);
extern void senser_set_lux(unsigned int now);

#endif /* INC_USER_SENSER_H_ */
