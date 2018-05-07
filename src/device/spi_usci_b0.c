/*
 * spi_usci_b0.c
 *
 *  Created on: 2016-03-22
 *      Author: Jack Chen <redchenjs@live.com>
 * 
 * ---------SPI---------
 * PORT		TYPE	PIN
 * MOSI		OUT		P1.7
 * MISO		IN		P1.6
 * SCK      OUT     P1.5
 * ---------------------
 */

#include <msp430.h>

#define SPI_SET_PIN()   {\
                            P1SEL |= BIT5 + BIT6 + BIT7;\
                            P1SEL2|= BIT5 + BIT6 + BIT7;\
                            P1DIR |= BIT5 + BIT7;\
                         }

static unsigned char *spi_tx_buff = 0;
static unsigned char *spi_rx_buff = 0;

static unsigned char spi_tx_num = 0;
static unsigned char spi_rx_num = 0;

void spi_init(void)
{
    SPI_SET_PIN();

    UCB0CTL1 |= UCSWRST;

    UCB0CTL0 |= UCMST + UCSYNC + UCCKPL + UCMSB;
    UCB0CTL1 |= UCSSEL_2;
    UCB0BR0  = 1;
    UCB0BR1  = 0;

    UCB0CTL1 &=~UCSWRST;

    UC0IFG &=~(UCB0RXIFG + UCB0TXIFG);
}

unsigned char spi_transmit_frame(unsigned char *p_buff, unsigned char num)
{
    if (num == 0) return 1;
    if (UCB0STAT & UCBUSY) return 0;
    __disable_interrupt();
    spi_tx_buff = p_buff;
    spi_tx_num  = num - 1;
    UC0IE &=~UCB0RXIE;
    UC0IE |= UCB0TXIE;
    __enable_interrupt();
    UCB0TXBUF = *spi_tx_buff;
    while (UCB0STAT & UCBUSY);
    return 1;
}

unsigned char spi_receive_frame(unsigned char *p_buff, unsigned char num)
{
    if (num == 0) return 1;
    if (UCB0STAT & UCBUSY) return 0;
    __disable_interrupt();
    spi_rx_buff = p_buff;
    spi_rx_num  = num - 1;
    UC0IE &=~UCB0TXIE;
    UC0IE |= UCB0RXIE;
    __enable_interrupt();
    UCB0TXBUF = 0xff;
    while (UCB0STAT & UCBUSY);
    return 1;
}

inline void spi_tx_isr_handle(void)
{
    UCB0RXBUF;
    if (spi_tx_num != 0) {
        spi_tx_num--;
        spi_tx_buff++;
        UCB0TXBUF = *spi_tx_buff;
    } else {
        UC0IFG &=~UCB0TXIFG;
        UC0IE  &=~(UCB0TXIE + UCB0RXIE);
    }
}

inline void spi_rx_isr_handle(void)
{
    *spi_rx_buff = UCB0RXBUF;
    if (spi_rx_num != 0) {
        spi_rx_num--;
        spi_rx_buff++;
        UCB0TXBUF = 0xff;
    } else {
        UC0IE &=~(UCB0TXIE + UCB0RXIE);
    }
    UC0IFG &=~UCB0TXIFG;
}
