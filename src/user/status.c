/*
 * status.c
 *
 *  Created on: 2017-03-19
 *      Author: Jack Chen <redchenjs@live.com>
 */

#include <user/link.h>
#include <user/motor.h>
#include <user/record.h>
#include <user/senser.h>
#include <user/display.h>
#include <user/terminal.h>

void status_update(void)
{
    static unsigned int cnt_above = 0;
    static unsigned int cnt_below = 0;

    if (mode_now == AUTO) {
        if (senser_lux_now >= senser_set_now) {
            cnt_above++;
        } else {
            cnt_below++;
        }

        if (cnt_above >= 1) {
            cnt_above = 0;
            if (display_index_now < 15) {
                display_index_now++;
            }
        }

        if (cnt_below >= 1) {
            cnt_below = 0;
            if (display_index_now > 0) {
                display_index_now--;
            }
        }

        if (display_index_now == 15 && motor_position_now != 0) {
            motor_set_position(0);
        }

        if (display_index_now == 0 && motor_position_now != 100) {
            motor_set_position(100);
        }
    }
}

void status_init(void)
{
    if (mode_now > 1) mode_now = 0;

    if (motor_position_now > 100) motor_position_now = 100;

    if (motor_status_now > 3) motor_status_now = 0;

    if (!motor_status_now) {
        display_index_now = 0;
    } else {
        display_index_now = 15;
    }
}
