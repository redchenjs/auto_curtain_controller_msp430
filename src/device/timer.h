/*
 * timer.h
 *
 *  Created on: 2016年11月9日
 *      Author: redchenjs
 */

#ifndef SRC_DEVICE_TIMER_H_
#define SRC_DEVICE_TIMER_H_

void timer_pwm_init(void);
void timer_pwm_start(void);
void timer_pwm_stop(void);

void timer_cap_init(void);
void timer_cap_start(void);
void timer_cap_stop(void);

#endif /* SRC_DEVICE_TIMER_H_ */
