#ifndef SPI_H_
#define SPI_H_

extern void spi_init(void);

extern unsigned char spi_transmit_frame(unsigned char *p_buff, unsigned char num);
extern unsigned char spi_receive_frame(unsigned char *p_buff, unsigned char num);

#endif /* SPI_H_ */
