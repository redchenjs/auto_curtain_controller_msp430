/* Includes ------------------------------------------------------------------*/
#include "../system/config.h"

void system_init(void)
{
	bcs_init();
//	gpio_init();

//	timerA0_init();
	spi_init();
	ssd1331_init();
	motor_init();

	wdt_init();
}
