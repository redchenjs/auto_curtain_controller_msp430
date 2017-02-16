/*
 * display.c
 *
 *  Created on: 2016年10月20日
 *      Author: redchenjs
 */
#include <stdio.h>
#include "../driver/ssd1331.h"

unsigned char init_flag=0;

extern unsigned int lux_now;
extern unsigned int lux_past;

extern unsigned int set_now;
extern unsigned int set_past;

extern unsigned char status_now;
extern unsigned char status_past;

extern unsigned char index_now;
extern unsigned char index_past;

const char disp_mask[8]  = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00};
const char prog_mask[17] = {0x2d,0x2d,0x2d,0x2d,0x2d,0x2d,0x2d,0x2d,0x2d,0x2d,0x2d,0x2d,0x2d,0x2d,0x2d,0x2d,0x00};

void display_refresh_lux(void)
{
	static char lux_disp[6];

	if (lux_now != lux_past) {
		sprintf(lux_disp, "%5u", lux_now);
		ssd1331_display_string(32, 0, disp_mask, FONT_1206, BLACK);
		ssd1331_display_string(44, 0, lux_disp, FONT_1206, YELLOW);
	}

	lux_past = lux_now;
}

void display_refresh_set(void)
{
	static char set_disp[6];

	if (set_now != set_past) {
		sprintf(set_disp, "%5u", set_now);
		ssd1331_display_string(32, 16, disp_mask, FONT_1206, BLACK);
		ssd1331_display_string(44, 16, set_disp, FONT_1206, PURPLE);
	}

	set_past = set_now;
}

void display_refresh_status(void)
{
	if ((status_now != status_past) || init_flag) {
		ssd1331_display_string(54, 32, disp_mask, FONT_1206, BLACK);
		switch (status_now) {
			case 0:
				ssd1331_display_string(60, 32, "closed", FONT_1206, RED);
				break;
			case 1:
				ssd1331_display_string(60, 32, "opened", FONT_1206, GREEN);
				break;
			case 2:
				ssd1331_display_string(54, 32, "closing", FONT_1206, YELLOW);
				break;
			case 3:
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
		switch (status_now) {
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

	if (index_now != index_past) {
		if (index_now > index_past) {
			ssd1331_display_string(index_now*6-6, 48, "-", FONT_1206, GREEN);
		}
		else {
			ssd1331_display_string(index_now*6+6, 48, "-", FONT_1206, RED);
		}
	}
	else if (index_now == 15) {
		ssd1331_display_string(index_now*6, 48, "-", FONT_1206, GREEN);
	}
	else if (index_now == 0) {
		ssd1331_display_string(index_now*6, 48, "-", FONT_1206, RED);
	}

	index_past = index_now;
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

	init_flag = 0;
}
