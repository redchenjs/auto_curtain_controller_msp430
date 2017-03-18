/*
 * bluetooth.h
 *
 *  Created on: 2017-3-9
 *      Author: redchenjs
 */

#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

extern unsigned int blu_link_status;

enum blu_status {
    ONLINE  = 0x1,
    OFFLINE = 0x0
};

extern void blu_refresh(void);

extern void blu_init(void);

#endif /* INC_DRIVER_BLUETOOTH_H_ */
