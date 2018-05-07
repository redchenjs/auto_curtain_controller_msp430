/*
 * uart_usci_a0.c
 *
 *  Created on: 2017-02-19
 *      Author: Jack Chen <redchenjs@live.com>
 */

#include <msp430.h>

#define RX_BUFF_SIZE 32

static unsigned char *uart_tx_buff = 0;
static unsigned char uart_rx_buff[RX_BUFF_SIZE] = {0};

static unsigned char uart_tx_num = 0;
static unsigned char uart_rx_num = 0;

void uart_init(void)
{
    P1SEL  |= BIT1 + BIT2;
    P1SEL2 |= BIT1 + BIT2;

    UCA0CTL1 |= UCSWRST;

    UCA0CTL1 |= UCSSEL_2;
    UCA0BR0  = 139;
    UCA0BR1  = 0;
    UCA0MCTL = UCBRS0;

    UCA0CTL1 &=~UCSWRST;

    UC0IFG &=~(UCA0RXIFG + UCA0TXIFG);

    UC0IE |= UCA0RXIE;
}

unsigned char uart_transmit_frame(unsigned char *p_buff, unsigned char num)
{
    if (num == 0) return 1;
    if (UCA0STAT & UCBUSY) return 0;
    __disable_interrupt();
    UC0IE |= UCA0TXIE;
    __enable_interrupt();
    uart_tx_buff = p_buff;
    uart_tx_num  = num-1;
    UCA0TXBUF = *uart_tx_buff;
    while (UCA0STAT & UCBUSY);
    return 1;
}

unsigned char uart_receive_frame(unsigned char *p_buff, unsigned char num)
{
    unsigned char cnt=0;
    if (num == 0 || uart_rx_num == 0) return 0;
    p_buff += uart_rx_num;
    __disable_interrupt();
    do {
        *--p_buff = uart_rx_buff[--uart_rx_num];
        cnt++;
    } while (uart_rx_num > 0);
    uart_rx_num = 0;
    __enable_interrupt();
    return cnt;
}

inline void uart_tx_isr_handle(void)
{
    if (uart_tx_num != 0) {
        uart_tx_num--;
        uart_tx_buff++;
        UCA0TXBUF = *uart_tx_buff;
    } else {
        UC0IFG &=~UCA0TXIFG;
        UC0IE  &=~UCA0TXIE;
    }
}

inline void uart_rx_isr_handle(void)
{
    if (uart_rx_num == RX_BUFF_SIZE) {
        uart_rx_num = RX_BUFF_SIZE - 1;
    }
    uart_rx_buff[uart_rx_num++] = UCA0RXBUF;
}
