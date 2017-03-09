/*
 * uart.h
 *
 *  Created on: 2017年2月19日
 *      Author: redchenjs
 */

#ifndef UART_H_
#define UART_H_

extern void uart_init(void);

extern unsigned char uart_transmit_frame(unsigned char *p_buff, unsigned char num);

#endif /* SRC_INTERFACE_UART_H_ */
