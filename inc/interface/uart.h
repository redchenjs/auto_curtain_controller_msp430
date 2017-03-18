/*
 * uart.h
 *
 *  Created on: 2017-2-19
 *      Author: redchenjs
 */

#ifndef UART_H_
#define UART_H_

extern void uart_init(void);

extern unsigned char uart_transmit_frame(unsigned char *p_buff, unsigned char num);
extern unsigned char uart_receive_frame(unsigned char *p_buff, unsigned char num);

extern void uart_tx_isr_handle(void);
extern void uart_rx_isr_handle(void);

#endif /* UART_H_ */
