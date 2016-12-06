/*
 * display.c
 *
 *  Created on: 2016年10月20日
 *      Author: redchenjs
 */
#include "display.h"

static bool init_flag=0;

extern uint16_t lux_now;
extern uint16_t lux_past;

extern uint16_t set_now;
extern uint16_t set_past;

extern uint8_t status_now;
extern uint8_t status_past;

extern uint8_t index_now;
extern uint8_t index_past;

const char disp_mask[7]  = {0xff,0xff,0xff,0xff,0xff,0xff,0xff};
const char prog_mask[16] = {0x2d,0x2d,0x2d,0x2d,0x2d,0x2d,0x2d,0x2d,0x2d,0x2d,0x2d,0x2d,0x2d,0x2d,0x2d,0x2d};

void display_init(void)
{
	init_flag = 1;

	ssd1331_display_string(0, 0, "now:", FONT_1206, WHITE);
	ssd1331_display_string(78, 0, "lux", FONT_1206, WHITE);

	ssd1331_display_string(0, 16, "set:", FONT_1206, WHITE);
	ssd1331_display_string(78, 16, "lux", FONT_1206, WHITE);

	ssd1331_display_string(0, 32, "status:", FONT_1206, WHITE);
	display_refreshStatus();

	display_refreshProgress();

	init_flag = 0;
}

void display_refreshLux(void)
{
	static char lux_disp[5];

	if (lux_now != lux_past) {
		sprintf(lux_disp, "%5u", lux_now);
		ssd1331_display_string(32, 0, disp_mask, FONT_1206, BLACK);
		ssd1331_display_string(44, 0, lux_disp, FONT_1206, YELLOW);
	}

	lux_past = lux_now;
}

void display_refreshSet(void)
{
	static char set_disp[5];

	if (set_now != set_past) {
		sprintf(set_disp, "%5u", set_now);
		ssd1331_display_string(32, 16, disp_mask, FONT_1206, BLACK);
		ssd1331_display_string(44, 16, set_disp, FONT_1206, PURPLE);
	}

	set_past = set_now;
}

void display_refreshStatus(void)
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

void display_refreshProgress(void)
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
