/*
 * spi.h
 *
 *  Created on: 2016-03-22
 *      Author: Jack Chen <redchenjs@live.com>
 */

#ifndef INC_CHIP_SPI_H_
#define INC_CHIP_SPI_H_

extern void spi_init(void);

extern unsigned char spi_transmit_frame(unsigned char *p_buff, unsigned char num);
extern unsigned char spi_receive_frame(unsigned char *p_buff, unsigned char num);

extern void spi_tx_isr_handle(void);
extern void spi_rx_isr_handle(void);

#endif /* INC_CHIP_SPI_H_ */
