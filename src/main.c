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

#include "system/init.h"
#include "system/user.h"

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    device_init();
    driver_init();

    user_init();

    while (1) {
        user_loop();

        __bis_SR_register(LPM0_bits + GIE);
    }
}
