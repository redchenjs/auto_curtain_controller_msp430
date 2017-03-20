#include "user/motor.h"
#include "user/record.h"
#include "user/display.h"
#include "driver/stepper.h"
#include "user/terminal.h"
/*
 * motor.c
 *
 *  Created on: 2016-9-27
 *      Author: redchenjs
 */
unsigned char motor_status_now  = CLOSED;
unsigned char motor_status_past = CLOSED;

void motor_update(void)
{
    motor_status_past = motor_status_now;
    if (stepper_ready) {
        switch (motor_status_now) {
            case CLOSED:
            case OPENED:
                if (stepper_location_now > stepper_location_set) {
                    motor_status_now = OPENING;
                    stepper_update();
                }
                else if (stepper_location_now < stepper_location_set) {
                    motor_status_now = CLOSING;
                    stepper_update();
                }
                break;
            case CLOSING:
            case OPENING:
                motor_status_now -= 2;
                record_write_all();
                break;
            default:
                break;
        }
	}
}

void motor_set_position(unsigned int value)
{
    stepper_location_set = value;
}

void motor_init(void)
{

}
