/*
 * motor.c
 *
 *  Created on: 2016年9月27日
 *      Author: redchenjs
 */
#include "../system/config.h"

uint8_t status_now  = 0x00;
uint8_t status_past = 0xff;

Stepper motor(64, 16, 24, 23);

void motor_init(void)
{
	motor.setSpeed(6000);
}

void motor_open(void)
{
	motor.step(300*3*4);
}

void motor_close(void)
{
	motor.step(-300*3*4);
}

void motor_set(void)
{
	if (status_now != status_past) {
		if (status_now == 2 && status_past == 1)
			motor_close();
		else if (status_now == 3 && status_past == 0)
			motor_open();
		else
			record_writeStatus();
	}

	status_past = status_now;

	if (motor.ready) {
		if (status_now == 2) {
			status_now = 0;
		}
		else if (status_now == 3) {
			status_now = 1;
		}
	}
}
