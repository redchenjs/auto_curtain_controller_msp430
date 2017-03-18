#include "user/motor.h"
#include "user/record.h"
#include "driver/stepper.h"
/*
 * motor.c
 *
 *  Created on: 2016-9-27
 *      Author: redchenjs
 */
unsigned char motor_status_now  = CLOSED;
unsigned char motor_status_past = CLOSED;

void motor_update(void)
{
	if (motor_status_now != motor_status_past) {
		if (motor_status_now == CLOSING)
			stepper_step(2000, FORWARD);
		else if (motor_status_now == OPENING)
			stepper_step(2000, BACKWARD);
		else
		    record_write_all();
	}

	motor_status_past = motor_status_now;

	if (stepper_ready) {
		if (motor_status_now == CLOSING) {
			motor_status_now = CLOSED;
		}
		else if (motor_status_now == OPENING) {
			motor_status_now = OPENED;
		}
	}
}

void motor_init(void)
{

}
