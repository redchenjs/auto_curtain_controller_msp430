#include <stdio.h>
#include "../user/motor.h"
#include "../user/senser.h"
#include "../system/fonts.h"
#include "../driver/ssd1331.h"
/*
 * display.c
 *
 *  Created on: 2016年10月20日
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

	if (senser_lux_now != senser_lux_past) {
		sprintf(disp_lux, "%5u", senser_lux_now);
		ssd1331_display_string(32, 0, disp_mask, FONT_1206, BLACK);
		ssd1331_display_string(44, 0, disp_lux, FONT_1206, YELLOW);
	}

	senser_lux_past = senser_lux_now;
}

void display_refresh_set(void)
{
	static char disp_set[6];

	if (senser_set_now != senser_set_past) {
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
			case MOTOR_CLOSED:
				ssd1331_display_string(60, 32, "closed", FONT_1206, RED);
				break;
			case MOTOR_OPENED:
				ssd1331_display_string(60, 32, "opened", FONT_1206, GREEN);
				break;
			case MOTOR_CLOSING:
				ssd1331_display_string(54, 32, "closing", FONT_1206, YELLOW);
				break;
			case MOTOR_OPENING:
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
            case 0:
            case 2:
                ssd1331_display_string(0, 48, prog_mask, FONT_1206, RED);
                break;
            case 1:
            case 3:
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

void display_init(void)
{
	init_flag = 1;

	ssd1331_display_string(0, 0, "now:", FONT_1206, WHITE);
	ssd1331_display_string(78, 0, "lux", FONT_1206, WHITE);
	ssd1331_display_string(0, 16, "set:", FONT_1206, WHITE);
	ssd1331_display_string(78, 16, "lux", FONT_1206, WHITE);
	ssd1331_display_string(0, 32, "status:", FONT_1206, WHITE);

	display_refresh_status();

	display_refresh_progress();

//	ssd1331_draw_bitmap(42, 35, &c_chBluetooth88[0], 8, 8, BLUE);

	init_flag = 0;
}
