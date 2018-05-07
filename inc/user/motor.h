/*
 * motor.h
 *
 *  Created on: 2016-09-27
 *      Author: Jack Chen <redchenjs@live.com>
 */

#ifndef INC_USER_MOTOR_H_
#define INC_USER_MOTOR_H_

enum motor_status_table {
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

#endif /* INC_USER_MOTOR_H_ */
