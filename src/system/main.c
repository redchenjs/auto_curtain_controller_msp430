#include "../system/config.h"
/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	
    system_init();

    user_init();

    while (1) {
    	user_loop();

    	__bis_SR_register(LPM0_bits + GIE);
    }
}
