#include <module/display.h>
#include <module/link.h>
#include <module/motor.h>
#include <module/record.h>
#include <module/senser.h>
#include <module/status.h>
#include <module/terminal.h>
/*
 * user.c
 *
 *  Created on: 2016-10-21
 *      Author: redchenjs
 */

void user_init(void)
{
	record_read_all();

	status_init();

	motor_init();

	display_init();

	terminal_init();
}

void user_loop(void)
{
    terminal_update();

	senser_update();

	link_update();

	status_update();

    motor_update();

	display_update();
}
