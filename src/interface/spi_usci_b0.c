#include <msp430.h>
/*
 * ---------SPI---------
 * PORT		TYPE	PIN
 * SCK		OUT		P1.5
 * STE		OUT		P1.4
 * MOSI		OUT		P1.7
 * MISO		IN		P1.6
 * ---------------------
 */
#define SPI_SET_PIN()   {\
                            P1SEL |= BIT5 + BIT6 + BIT7;\
                            P1SEL2|= BIT5 + BIT6 + BIT7;\
                            P1DIR |= BIT5 + BIT7;\
                            P1REN |= BIT6;\
                            P1OUT |= BIT6;\
                         }

unsigned char *spi_tx_buff;
unsigned char *spi_rx_buff;

unsigned char spi_tx_num = 0;
unsigned char spi_rx_num = 0;

void spi_init(void)
{
    SPI_SET_PIN();

    UCB0CTL1 |= UCSWRST;

    UCB0CTL0 = UCCKPL + UCMSB + UCMST + UCMODE_0 + UCSYNC;
    UCB0CTL1 = UCSWRST + UCSSEL_2;
    UCB0BR0  = 0;
    UCB0BR1  = 0;

    UCB0CTL1 &=~UCSWRST;

    IFG2 &=~(UCB0RXIFG + UCB0TXIFG);
}

unsigned char spi_transmit_frame(unsigned char *p_buff, unsigned char num)
{
	if (num == 0) return 1;
	__disable_interrupt();
	spi_tx_buff = p_buff;
	spi_tx_num  = num - 1;
	IE2 &=~UCB0RXIE;
	IE2 |= UCB0TXIE;
	__enable_interrupt();
	UCB0TXBUF = *spi_tx_buff;
    while (UCA0STAT & UCBUSY);
	return 1;
}

unsigned char spi_receive_frame(unsigned char *p_buff, unsigned char num)
{
	if (num == 0) return 1;
	__disable_interrupt();
    spi_rx_buff = p_buff;
    spi_rx_num  = num - 1;
	IE2 &=~UCB0TXIE;
	IE2 |= UCB0RXIE;
    __enable_interrupt();
    UCB0TXBUF = 0xff;
    while (UCA0STAT & UCBUSY);
	return 1;
}

#pragma vector=USCIAB0TX_VECTOR
__interrupt void usciab0_tx_isr(void)
{
	UCB0RXBUF;
	if (spi_tx_num != 0) {
		spi_tx_num--;
		spi_tx_buff++;
		UCB0TXBUF = *spi_tx_buff;
	}
	else {
		IFG2 &=~UCB0TXIFG;
		IE2 &=~(UCB0TXIE + UCB0RXIE);
	}
}

#pragma vector=USCIAB0RX_VECTOR
__interrupt void usciab0_rx_isr(void)
{
	*spi_rx_buff = UCB0RXBUF;
	if (spi_rx_num != 0) {
		spi_rx_num--;
		spi_rx_buff++;
		UCB0TXBUF = 0xff;
	}
	else {
		IE2 &=~(UCB0TXIE + UCB0RXIE);
	}
	IFG2 &=~UCB0TXIFG;
}
