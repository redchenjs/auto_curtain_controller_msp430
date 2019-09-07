/*
 * link.c
 *
 *  Created on: 2017-03-16
 *      Author: Jack Chen <redchenjs@live.com>
 */

#include "board/bluetooth.h"

unsigned int link_status_now  = OFFLINE;
unsigned int link_status_past = OFFLINE;

void link_update(void)
{
    blu_refresh();

    link_status_past = link_status_now;

    if (link_status_now != blu_link_status) {
        link_status_now = blu_link_status;
    }
}
