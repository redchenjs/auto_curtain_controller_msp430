/*
 * bluetooth.h
 *
 *  Created on: 2017-03-09
 *      Author: Jack Chen <redchenjs@live.com>
 */

#ifndef INC_BOARD_BLUETOOTH_H_
#define INC_BOARD_BLUETOOTH_H_

extern unsigned int blu_link_status;

enum blutooth_status_table {
    OFFLINE = 0x00,
    ONLINE  = 0x01
};

extern void blu_refresh(void);
extern void blu_init(void);

#endif /* INC_BOARD_BLUETOOTH_H_ */
