/*
 * motor.h
 *
 *  Created on: 2016-9-27
 *      Author: redchenjs
 */

#ifndef MOTOR_H_
#define MOTOR_H_

enum motor_status {
    CLOSED  = 0x0,
    OPENED  = 0x1,
    CLOSING = 0x2,
    OPENING = 0x3
};

extern unsigned char motor_status_now;
extern unsigned char motor_status_past;

extern void motor_init(void);
extern void motor_step(int num);
extern void motor_update(void);
extern void motor_set_position(unsigned int value);

#endif
