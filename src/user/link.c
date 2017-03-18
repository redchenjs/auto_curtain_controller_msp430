#include <driver/bluetooth.h>
/*
 * link.c
 *
 *  Created on: 2017-3-16
 *      Author: redchenjs
 */
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
