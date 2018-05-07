/*
 * display.h
 *
 *  Created on: 2016-10-20
 *      Author: Jack Chen <redchenjs@live.com>
 */

#ifndef INC_USER_DISPLAY_H_
#define INC_USER_DISPLAY_H_

extern unsigned char display_index_now;
extern unsigned char display_index_past;

extern void display_update(void);
extern void display_init(void);

#endif /* INC_USER_DISPLAY_H_ */
