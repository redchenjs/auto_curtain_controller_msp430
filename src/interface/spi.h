#ifndef SPI_H_
#define SPI_H_
#include "config.h"
/*
 * ---------SPI---------
 * PORT		TYPE	PIN
 * SCK		OUT		P2.0
 * STE		OUT		NC
 * MOSI		OUT		P2.1
 * MISO		IN		P2.2
 * ---------------------
 */
#define SPI_PIN_SET			P1DIR |= BIT4; P1DIR |= BIT2; P1DIR &=~BIT1

#define SPI_CLK_HIGH		P1OUT |= BIT4
#define SPI_CLK_LOW			P1OUT &=~BIT4

#define SPI_MOSI_HIGH		P1OUT |= BIT2
#define SPI_MOSI_LOW		P1OUT &=~BIT2

#define SPI_MISO_IN			P1IN  &  BIT1

#define	SOFT_SPI

void spi_init(void);
void spi_lowSpeed(void);
void spi_highSpeed(void);

uint8_t spi_txFrame(uint8_t *pBuffer, uint16_t size);
uint8_t spi_txFrame(uint8_t *pBuffer, uint16_t size);

#endif /* SPI_H_ */
