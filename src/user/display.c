/*
 * display.c
 *
 *  Created on: 2016-10-20
 *      Author: Jack Chen <redchenjs@live.com>
 */

#include <stdio.h>

#include "driver/ssd1331.h"
#include "driver/bluetooth.h"

#include "system/fonts.h"

#include "user/link.h"
#include "user/motor.h"
#include "user/senser.h"
#include "user/terminal.h"

static unsigned char init_flag = 0;

unsigned char display_index_now  = 0x00;
unsigned char display_index_past = 0xff;

static const unsigned char icon_mask[8] = { 0x00, 0x42, 0x24, 0xFF, 0x99, 0x5A, 0x24, 0x00 };
static const char prog_mask[17] = {
    0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x00
};

void display_refresh_lux(void)
{
    static char disp_lux[6];

    if (senser_lux_now != senser_lux_past || init_flag) {
        sprintf(disp_lux, "%5u", senser_lux_now);
        ssd1331_display_string(48, 0, disp_lux, FONT_1206, Yellow, Black);
    }

    senser_lux_past = senser_lux_now;
}

void display_refresh_set(void)
{
    static char disp_set[6];

    if (senser_set_now != senser_set_past || init_flag) {
        sprintf(disp_set, "%5u", senser_set_now);
        ssd1331_display_string(48, 16, disp_set, FONT_1206, Purple, Black);
    }

    senser_set_past = senser_set_now;
}

void display_refresh_status(void)
{
    if ((motor_status_now != motor_status_past) || init_flag) {
        switch (motor_status_now) {
            case CLOSED:
                ssd1331_display_string(54, 32, " closed", FONT_1206, Red, Black);
                break;
            case OPENED:
                ssd1331_display_string(54, 32, " opened", FONT_1206, Lime, Black);
                break;
            case CLOSING:
                ssd1331_display_string(54, 32, "closing", FONT_1206, Yellow, Black);
                break;
            case OPENING:
                ssd1331_display_string(54, 32, "opening", FONT_1206, Yellow, Black);
                break;
            default:
                break;
        }
    }
}

void display_refresh_progress(void)
{
    if (init_flag) {
        switch (motor_status_now) {
            case CLOSED:
            case CLOSING:
                ssd1331_display_string(0, 48, prog_mask, FONT_1206, Red, Black);
                break;
            case OPENED:
            case OPENING:
                ssd1331_display_string(0, 48, prog_mask, FONT_1206, Lime, Black);
                break;
            default:
                break;
        }
    }

    if (display_index_now != display_index_past) {
        if (display_index_now > display_index_past) {
            ssd1331_display_string(display_index_now*6-6, 48, "-", FONT_1206, Lime, Black);
        } else {
            ssd1331_display_string(display_index_now*6+6, 48, "-", FONT_1206, Red, Black);
        }
    } else if (display_index_now == 15) {
        ssd1331_display_string(display_index_now*6, 48, "-", FONT_1206, Lime, Black);
    } else if (display_index_now == 0) {
        ssd1331_display_string(display_index_now*6, 48, "-", FONT_1206, Red, Black);
    }

    display_index_past = display_index_now;
}

void display_refresh_link(void)
{
    static unsigned char cnt;

    if ((link_status_now != link_status_past) || init_flag) {
        switch (link_status_now) {
            case OFFLINE:
                ssd1331_draw_mono_bitmap(44, 34, &icon_mask[0], 8, 8, Black, Black);
                break;
            case ONLINE:
                ssd1331_draw_mono_bitmap(44, 34, &icon_mask[0], 8, 8, Blue, Black);
                break;
            default:
                break;
        }
    }

    if (link_status_now) {
        if (cnt++ & 0x01) {
            ssd1331_draw_mono_bitmap(44, 34, &icon_mask[0], 8, 8, Lime, Black);
        } else {
            ssd1331_draw_mono_bitmap(44, 34, &icon_mask[0], 8, 8, Blue, Black);
        }
    }
}

void display_update(void)
{
    display_refresh_lux();
    display_refresh_set();
    display_refresh_status();
    display_refresh_progress();
    display_refresh_link();
}

void display_init(void)
{
    init_flag = 1;

    ssd1331_display_string(0, 0, "now:", FONT_1206, White, Black);
    ssd1331_display_string(84, 0, "lx", FONT_1206, White, Black);
    ssd1331_display_string(0, 16, "set:", FONT_1206, White, Black);
    ssd1331_display_string(84, 16, "lx", FONT_1206, White, Black);
    ssd1331_display_string(0, 32, "status:", FONT_1206, White, Black);

    display_update();

    init_flag = 0;
}
