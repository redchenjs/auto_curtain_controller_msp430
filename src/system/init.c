#include "inc/device/bcs.h"
#include "inc/device/wdt.h"
#include "inc/device/i2c.h"
#include "inc/device/spi.h"
#include "inc/device/uart.h"
#include "inc/driver/bh1750.h"
#include "inc/driver/ssd1331.h"
#include "inc/driver/stepper.h"

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

void system_init(void)
{
    device_init();

    driver_init();
}
