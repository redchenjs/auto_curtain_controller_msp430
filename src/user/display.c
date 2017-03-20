#include <stdio.h>
#include "user/link.h"
#include "user/motor.h"
#include "user/senser.h"
#include "user/terminal.h"
#include "system/fonts.h"
#include "driver/stepper.h"
#include "driver/ssd1331.h"
#include "driver/bluetooth.h"
/*
 * display.c
 *
 *  Created on: 2016-10-20
 *      Author: redchenjs
 */
static unsigned char init_flag = 0;

unsigned char display_index_now  = 0x00;
unsigned char display_index_past = 0xff;

static const char disp_mask[8]  = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00};
static const char prog_mask[17] = {0x2d,0x2d,0x2d,0x2d,0x2d,0x2d,0x2d,0x2d,0x2d,0x2d,0x2d,0x2d,0x2d,0x2d,0x2d,0x2d,0x00};

void display_refresh_lux(void)
{
	static char disp_lux[6];

	if (senser_lux_now != senser_lux_past || init_flag) {
		sprintf(disp_lux, "%5u", senser_lux_now);
		ssd1331_display_string(32, 0, disp_mask, FONT_1206, BLACK);
		ssd1331_display_string(44, 0, disp_lux, FONT_1206, YELLOW);
	}

	senser_lux_past = senser_lux_now;
}

void display_refresh_set(void)
{
	static char disp_set[6];

	if (senser_set_now != senser_set_past || init_flag) {
	    sprintf(disp_set, "%5u", senser_set_now);
		ssd1331_display_string(32, 16, disp_mask, FONT_1206, BLACK);
		ssd1331_display_string(44, 16, disp_set, FONT_1206, PURPLE);
	}

	senser_set_past = senser_set_now;
}

void display_refresh_status(void)
{
	if ((motor_status_now != motor_status_past) || init_flag) {
		ssd1331_display_string(54, 32, disp_mask, FONT_1206, BLACK);
		switch (motor_status_now) {
			case CLOSED:
				ssd1331_display_string(60, 32, "closed", FONT_1206, RED);
				break;
			case OPENED:
				ssd1331_display_string(60, 32, "opened", FONT_1206, GREEN);
				break;
			case CLOSING:
				ssd1331_display_string(54, 32, "closing", FONT_1206, YELLOW);
				break;
			case OPENING:
				ssd1331_display_string(54, 32, "opening", FONT_1206, YELLOW);
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
                ssd1331_display_string(0, 48, prog_mask, FONT_1206, RED);
                break;
            case OPENED:
            case OPENING:
                ssd1331_display_string(0, 48, prog_mask, FONT_1206, GREEN);
                break;
            default:
                break;
        }
	}

	if (display_index_now != display_index_past) {
		if (display_index_now > display_index_past) {
			ssd1331_display_string(display_index_now*6-6, 48, "-", FONT_1206, GREEN);
		}
		else {
			ssd1331_display_string(display_index_now*6+6, 48, "-", FONT_1206, RED);
		}
	}
	else if (display_index_now == 15) {
		ssd1331_display_string(display_index_now*6, 48, "-", FONT_1206, GREEN);
	}
	else if (display_index_now == 0) {
		ssd1331_display_string(display_index_now*6, 48, "-", FONT_1206, RED);
	}

	display_index_past = display_index_now;
}

void display_refresh_link(void)
{
    static unsigned char cnt;

    if ((link_status_now != link_status_past) || init_flag) {
        switch (link_status_now) {
            case OFFLINE:
                ssd1331_draw_bitmap(44, 34, &c_chBluetooth88[0], 8, 8, BLACK);
                break;
            case ONLINE:
                ssd1331_draw_bitmap(44, 34, &c_chBluetooth88[0], 8, 8, BLUE);
                break;
            default:
                break;
        }
    }

    if (link_status_now) {
        if (cnt++ & 0x01)
            ssd1331_draw_bitmap(44, 34, &c_chBluetooth88[0], 8, 8, GREEN);
        else
            ssd1331_draw_bitmap(44, 34, &c_chBluetooth88[0], 8, 8, BLUE);
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

	ssd1331_display_string(0, 0, "now:", FONT_1206, WHITE);
	ssd1331_display_string(78, 0, "lux", FONT_1206, WHITE);
	ssd1331_display_string(0, 16, "set:", FONT_1206, WHITE);
	ssd1331_display_string(78, 16, "lux", FONT_1206, WHITE);
	ssd1331_display_string(0, 32, "status:", FONT_1206, WHITE);

	display_refresh_lux();

	display_refresh_set();

	display_refresh_status();

	display_refresh_progress();

	display_refresh_link();

	init_flag = 0;
}
