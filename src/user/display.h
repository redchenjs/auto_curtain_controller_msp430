/*
 * display.h
 *
 *  Created on: 2016年10月20日
 *      Author: redchenjs
 */

#ifndef SRC_USER_DISPLAY_H_
#define SRC_USER_DISPLAY_H_

#include "config.h"

void display_refreshLux(void);
void display_refreshSet(void);
void display_refreshStatus(void);
void display_refreshProgress(void);

void display_init(void);

#endif /* SRC_USER_DISPLAY_H_ */
