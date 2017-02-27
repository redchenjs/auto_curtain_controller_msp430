#include "../user/motor.h"
#include "../user/record.h"
#include "../driver/stepper.h"
/*
 * motor.c
 *
 *  Created on: 2016年9月27日
 *      Author: redchenjs
 */

unsigned char motor_status_now  = 0x00;
unsigned char motor_status_past = 0xff;

void motor_update(void)
{
	if (motor_status_now != motor_status_past) {
		if (motor_status_now == MOTOR_CLOSING)
			stepper_step(2000, FORWARD);
		else if (motor_status_now == MOTOR_OPENING)
			stepper_step(2000, BACKWARD);
//		else
//			record_write_status();
	}

	motor_status_past = motor_status_now;

	if (stepper_ready) {
		if (motor_status_now == MOTOR_CLOSING) {
			motor_status_now = MOTOR_CLOSED;
		}
		else if (motor_status_now == MOTOR_OPENING) {
			motor_status_now = MOTOR_OPENED;
		}
	}
}

void motor_init(void)
{

}
