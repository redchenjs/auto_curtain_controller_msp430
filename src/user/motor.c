/*
 * motor.c
 *
 *  Created on: 2016年9月27日
 *      Author: redchenjs
 */
#include "../user/record.h"
#include "../user/display.h"

unsigned char status_now  = 0x00;
unsigned char status_past = 0xff;

extern unsigned char stepper_status;

void motor_init(void)
{
//	motor_setSpeed(6000);
}

void motor_open(void)
{
//	motor_step(300*3*4);
}

void motor_close(void)
{
//	motor_step(-300*3*4);
}

void motor_update(void)
{
	if (status_now != status_past) {
		if (status_now == 2 && status_past == 1)
			motor_close();
		else if (status_now == 3 && status_past == 0)
			motor_open();
		else
			record_write_status();
	}

	status_past = status_now;

	if (stepper_status) {
		if (status_now == 2) {
			status_now = 0;
		}
		else if (status_now == 3) {
			status_now = 1;
		}
	}
}
