/*
 * terminal.h
 *
 *  Created on: 2017-02-19
 *      Author: Jack Chen <redchenjs@live.com>
 */

#ifndef INC_USER_TERMINAL_H_
#define INC_USER_TERMINAL_H_

enum terminal_mode_table {
    AUTO   = 0x00,
    MANUAL = 0x01
};

extern unsigned char mode_now;
extern unsigned char mode_past;

extern void terminal_set_mode(unsigned int value);
extern void terminal_update(void);
extern void terminal_init(void);

#endif /* INC_USER_TERMINAL_H_ */
