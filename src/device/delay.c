/*
 * delay.c
 *
 *  Created on: 2016年9月27日
 *      Author: redchenjs
 */
#include <stdint.h>
#include <msp430g2553.h>

#define F_CPU 16000000

void delay_us(unsigned int cycles)
{
	while (cycles--)
		_delay_cycles(F_CPU/1000000);	//1us
}

void delay_ms(unsigned int cycles)
{
	while (cycles--)
		_delay_cycles(F_CPU/1000);	//1ms
}
