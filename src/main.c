/*
 * main.c
 *
 *  Created on: 2016-10-26
 *      Author: Jack Chen <redchenjs@live.com>
 *
 *                   MSP430G2553
 *                ------------------
 *     blu_txd-->|P1.1            NC|--x
 *     blu_rxd<--|P1.2          P1.0|--x
 *    blu_link-->|P1.3          DVCC|<--3.3v
 *     oled_cs<--|P1.4          AVCC|<--3.3v
 *    oled_clk<--|P1.5          DVSS|-->Gnd
 *  senser_sda<->|P3.1          AVSS|-->Gnd
 *  senser_scl<--|P3.0          P2.6|--x
 *            x--|NC            P2.7|--x
 *   stepper_a<--|P2.0          TEST|--x
 *   stepper_b<--|P2.1          RST#|--^
 *   stepper_c<--|P2.2          P1.7|-->oled_din
 *            x--|P3.2          P1.6|--x
 *            x--|P3.3          P3.7|-->oled_dc
 *            x--|P3.4          P3.6|-->oled_res
 *   stepper_d<--|P2.3          P3.5|--x
 *            x--|P2.4          P2.5|--x
 *                ------------------
 */

#include <msp430.h>

#include "chip/bcs.h"
#include "chip/wdt.h"
#include "chip/i2c.h"
#include "chip/spi.h"
#include "chip/uart.h"

#include "board/bh1750.h"
#include "board/ssd1331.h"
#include "board/stepper.h"

#include <user/link.h>
#include <user/motor.h>
#include <user/record.h>
#include <user/sensor.h>
#include <user/status.h>
#include <user/display.h>
#include <user/terminal.h>

static void chip_init(void)
{
    bcs_init();
    wdt_init();
    i2c_init();
    spi_init();
    uart_init();
}

static void board_init(void)
{
    bh1750_init();
    ssd1331_init();
    stepper_init();
}

static void user_init(void)
{
    record_read_all();
    status_init();
    motor_init();
    display_init();
    terminal_init();
}

static void user_loop(void)
{
    terminal_update();
    sensor_update();
    link_update();
    status_update();
    motor_update();
    display_update();
}

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

    chip_init();
    board_init();

    user_init();

    while (1) {
        user_loop();

        __bis_SR_register(LPM0_bits + GIE);
    }
}
