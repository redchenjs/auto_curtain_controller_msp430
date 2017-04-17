/*
 * terminal.h
 *
 *  Created on: 2017-2-19
 *      Author: redchenjs
 */

#ifndef TERMINAL_H_

enum terminal_mode {
    AUTO   = 0x00,
    MANUAL = 0x01
};

extern unsigned char mode_now;
extern unsigned char mode_past;

extern void terminal_set_mode(unsigned int value);

extern void terminal_update(void);

extern void terminal_init(void);

#endif /* TERMINAL_H_ */
