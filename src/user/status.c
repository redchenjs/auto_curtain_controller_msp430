#include "user/link.h"
#include "user/motor.h"
#include "user/record.h"
#include "user/senser.h"
#include "user/display.h"
#include "user/terminal.h"
#include "system/fonts.h"
#include "driver/stepper.h"
#include "driver/ssd1331.h"
#include "driver/bluetooth.h"
/*
 * status.c
 *
 *  Created on: 2017-3-19
 *      Author: redchenjs
 */

void status_update(void)
{
    static unsigned int cnt_above = 0;
    static unsigned int cnt_below = 0;

    if (mode_now == AUTO) {
        if (senser_lux_now >= senser_set_now) {
            cnt_above++;
        }
        else {
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

        if (display_index_now == 15 && stepper_location_set != 0){
            stepper_location_set = 0;
        }

        if (display_index_now == 0 && stepper_location_set != 2000){
            stepper_location_set = 2000;
        }
    }
}
