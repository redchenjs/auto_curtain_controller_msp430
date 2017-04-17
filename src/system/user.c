#include "inc/apps/display.h"
#include "inc/apps/link.h"
#include "inc/apps/motor.h"
#include "inc/apps/record.h"
#include "inc/apps/senser.h"
#include "inc/apps/status.h"
#include "inc/apps/terminal.h"
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
