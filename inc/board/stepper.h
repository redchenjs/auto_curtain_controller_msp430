/*
 * stepper.h
 *
 *  Created on: 2016-10-20
 *      Author: Jack Chen <redchenjs@live.com>
 */

#ifndef INC_BOARD_STEPPER_H_
#define INC_BOARD_STEPPER_H_

enum stepper_direction_table {
    FORWARD  = 0x00,
    BACKWARD = 0x01
};

extern unsigned char stepper_ready;

extern unsigned int stepper_location_now;
extern unsigned int stepper_location_set;

extern void stepper_update(void);
extern void stepper_init(void);
extern void stepper_step(unsigned int steps_to_move, unsigned char direction);

extern void stepper_timer_isr_handle(void);

#endif /* INC_BOARD_STEPPER_H_ */
