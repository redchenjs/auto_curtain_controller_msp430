/*
 * display.h
 *
 *  Created on: 2016年10月20日
 *      Author: redchenjs
 */
#ifndef DISPLAY_H_
#define DISPLAY_H_

extern unsigned char display_index_now;
extern unsigned char display_index_past;

extern void display_refresh_lux(void);
extern void display_refresh_set(void);
extern void display_refresh_status(void);
extern void display_refresh_progress(void);

extern void display_init(void);

#endif
