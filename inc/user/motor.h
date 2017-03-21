/*
 * motor.h
 *
 *  Created on: 2016-9-27
 *      Author: redchenjs
 */

#ifndef MOTOR_H_
#define MOTOR_H_

enum motor_status {
    CLOSED  = 0x00,
    OPENED  = 0x01,
    CLOSING = 0x02,
    OPENING = 0x03
};

extern unsigned char motor_position_now;
extern unsigned char motor_position_past;

extern unsigned char motor_status_now;
extern unsigned char motor_status_past;

extern void motor_init(void);
extern void motor_update(void);
extern void motor_set_position(unsigned char value);

#endif
