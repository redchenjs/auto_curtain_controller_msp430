/*
 * motor.h
 *
 *  Created on: 2016年9月27日
 *      Author: redchenjs
 */

#ifndef MOTOR_H_
#define MOTOR_H_

enum MotorState {
    MOTOR_CLOSED  = 0x0,
    MOTOR_OPENED  = 0x1,
    MOTOR_CLOSING = 0x2,
    MOTOR_OPENING = 0x3
};

extern unsigned char motor_status_now;
extern unsigned char motor_status_past;

extern void motor_init(void);
extern void motor_step(int num);
extern void motor_update(void);

#endif
