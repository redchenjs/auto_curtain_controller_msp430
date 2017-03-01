#include <msp430g2553.h>
/*
 * ---------SPI---------
 * PORT		TYPE	PIN
 * SCK		OUT		P1.5
 * STE		OUT		P1.4
 * MOSI		OUT		P1.7
 * MISO		IN		P1.6
 * ---------------------
 */
#define	HARD_SPI

#ifdef SOFT_SPI
#define SPI_CS_HIGH		P1OUT |= BIT4
#define SPI_CS_LOW		P1OUT &=~BIT4
#define SPI_CLK_HIGH	P1OUT |= BIT5
#define SPI_CLK_LOW		P1OUT &=~BIT5
#define SPI_MOSI_HIGH	P1OUT |= BIT7
#define SPI_MOSI_LOW	P1OUT &=~BIT7
#define SPI_MISO_IN		P1IN  &  BIT6

void spi_init(void)
{
	P1DIR |= BIT5;
	P1DIR |= BIT4;
	P1DIR |= BIT7;
	P1DIR &=~BIT6;
}

void spi_transmit_char(unsigned char data)
{
	unsigned char i=0;
	for (i=0; i<8; i++) {
		SPI_CLK_LOW;
		if ((data<<i) & BIT7)
			SPI_MOSI_HIGH;
		else
			SPI_MOSI_LOW;
		SPI_CLK_HIGH;
	}
}

unsigned char spi_receive_char(void)
{
	unsigned char i=0;
	unsigned char temp=0;
	for (i=0; i<8; i++) {
		SPI_CLK_LOW ;
		SPI_CLK_HIGH;
		temp = temp<<1;
		if(SPI_MISO_IN)
			temp |= BIT0;
	}
	return temp;
}

unsigned char spi_transmit_frame(unsigned char *p_buff, unsigned char num)
{
	unsigned char i=0;
	_disable_interrupts();
	for (i=0; i<num; i++) {
		spi_transmit_char(*p_buff);
		p_buff++;
	}
	_enable_interrupts();
	return 1;
}

unsigned char spi_receive_frame(unsigned char *p_buff, unsigned char num)
{
	unsigned char i=0;
	_disable_interrupts();
	for (i=0; i<num; i++) {
		 *p_buff = spi_receive_char();
		 p_buff++;
	}
	_enable_interrupts();
	return 1;
}

#endif		//End of SOFT_SPI

#ifdef HARD_SPI			//Begin of HRAD_SPI

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

#endif
