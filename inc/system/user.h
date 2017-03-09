/*
 * user.h
 *
 *  Created on: 2016年10月21日
 *      Author: redchenjs
 */

#ifndef USER_H_
#define USER_H_

enum status {
	CLOSED  = 0x0,
	OPENED  = 0x1,
	CLOSING = 0x2,
	OPENING = 0x3,
	MANUAL  = 0x4,
};

struct setting {
	enum status curtain_status;
	unsigned char curtain_progress;
	unsigned char link_status;
	unsigned int motor_location;
	unsigned int senser_set;
};

void user_init(void);
void user_loop(void);

#endif
