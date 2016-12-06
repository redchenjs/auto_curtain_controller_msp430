/*
 * delay.c
 *
 *  Created on: 2016年9月27日
 *      Author: redchenjs
 */
#include "delay.h"

void delay_us(uint16_t cycles)
{
//	_delay_cycles(MCLK_FREQ/1000);			//1000us延时
//	_delay_cycles(MCLK_FREQ/10000);			//100us延时
//	_delay_cycles(MCLK_FREQ/100000);		//10us延时
//	_delay_cycles(MCLK_FREQ/1000000);		//1us延时
//	_NOP();
	while (cycles--)
		_delay_cycles(F_CPU/1000000);		//1us延时;
}

void delay_ms(uint16_t cycles)
{
	while (cycles--)
		_delay_cycles(F_CPU/1000);		//1ms延时;
}
