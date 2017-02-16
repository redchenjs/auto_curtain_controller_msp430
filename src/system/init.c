#include "../device/bcs.h"
#include "../device/wdt.h"
#include "../interface/i2c.h"
#include "../interface/spi.h"
#include "../driver/bh1750.h"
#include "../driver/ssd1331.h"
#include "../driver/stepper.h"

void system_init(void)
{
	bcs_init();
	wdt_init();
	i2c_init();
	spi_init();
	bh1750_init();
	ssd1331_init();
	stepper_init();
}
