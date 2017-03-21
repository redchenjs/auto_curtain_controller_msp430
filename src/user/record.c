#include "device/bcs.h"
#include "user/motor.h"
#include "user/senser.h"
#include "user/display.h"
#include "user/terminal.h"
#include "device/flash.h"
#include "driver/stepper.h"
/*
 * record.c
 *
 *  Created on: 2016-10-26
 *      Author: redchenjs
 */
enum flash_address {
    MODE_SET_ADDRESS     = 0x00,
    SENSER_SET_ADDRESS   = 0x02,
    MOTOR_STATUS_ADDRESS = 0x04,
    MOTOR_POSITION_ADDRESS = 0x06
};
void record_write_all(void)
{
    flash_init(64, 'B');								// 初始化Flash
	flash_erase();									    // 擦除Info_B

    flash_direct_write_char(MOTOR_STATUS_ADDRESS, motor_status_now);
    flash_direct_write_char(MOTOR_POSITION_ADDRESS, motor_position_now);

    flash_direct_write_char(MODE_SET_ADDRESS, mode_now);
    flash_direct_write_word(SENSER_SET_ADDRESS, senser_set_now);
}

void record_read_all(void)
{
    flash_init(64, 'B');							    // 初始化Flash

    motor_status_now     = flash_read_char(MOTOR_STATUS_ADDRESS);
    motor_position_now   = flash_read_word(MOTOR_POSITION_ADDRESS);
    mode_now             = flash_read_char(MODE_SET_ADDRESS);
    senser_set_now       = flash_read_word(SENSER_SET_ADDRESS);
}
