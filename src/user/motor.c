/*
 * motor.c
 *
 *  Created on: 2016-09-27
 *      Author: Jack Chen <redchenjs@live.com>
 */

#include "driver/stepper.h"

#include "user/motor.h"
#include "user/record.h"
#include "user/display.h"

unsigned char motor_position_now  = 0;
unsigned char motor_position_past = 100;

unsigned char motor_status_now  = CLOSED;
unsigned char motor_status_past = CLOSED;

void motor_update(void)
{
    motor_status_past = motor_status_now;

    if (stepper_location_now > stepper_location_set) {
        motor_status_now = OPENING;
        stepper_update();
    } else if (stepper_location_now < stepper_location_set) {
        motor_status_now = CLOSING;
        stepper_update();
    }

    if (stepper_ready && (motor_status_now == CLOSING || motor_status_now == OPENING)) {
        motor_status_now -= 2;
        record_write_all();
    }
}

void motor_set_position(unsigned char value)
{
    motor_position_past = motor_position_now;
    if (value > 100) {
        value = 100;
    }
    motor_position_now  = value;
    stepper_location_set = (unsigned int)motor_position_now * 20;
}

void motor_init(void)
{
    stepper_location_set = (unsigned int)motor_position_now * 20;
    stepper_location_now = stepper_location_set;
}
