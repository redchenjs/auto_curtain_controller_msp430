#include <msp430.h>
#include "device/wdt.h"
#include "interface/spi.h"
#include "interface/uart.h"
#include "driver/stepper.h"
/*
 * vector.c
 *
 */
 #pragma vector=WDT_VECTOR
__interrupt void WDT_ISR(void)
{
    static unsigned int cnt = 0;

    if (cnt++ > 500) {
        cnt = 0;
        __bic_SR_register_on_exit(LPM0_bits);
    }
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void)
{
    stepper_timer_isr_handle();
}

#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void)
{
    if (UC0IFG & UCA0TXIFG) {
        uart_tx_isr_handle();
    }
    else if (UC0IFG & UCB0TXIFG) {
        spi_tx_isr_handle();
    }
}

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCIAB0RX_ISR(void)
{
    if (UC0IFG & UCA0RXIFG) {
        uart_rx_isr_handle();
    }
    else if (UC0IFG & UCB0RXIFG) {
        spi_rx_isr_handle();
    }
}
