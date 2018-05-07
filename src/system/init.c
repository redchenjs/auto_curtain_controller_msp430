/*
 * init.c
 *
 *  Created on: 2016-10-20
 *      Author: Jack Chen <redchenjs@live.com>
 */

#include "device/bcs.h"
#include "device/wdt.h"
#include "device/i2c.h"
#include "device/spi.h"
#include "device/uart.h"

#include "driver/bh1750.h"
#include "driver/ssd1331.h"
#include "driver/stepper.h"

void device_init(void)
{
    bcs_init();
    wdt_init();
    i2c_init();
    spi_init();
    uart_init();
}

void driver_init(void)
{
    bh1750_init();
    ssd1331_init();
    stepper_init();
}
