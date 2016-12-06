/*
 * gpio.c
 *
 *  Created on: 2016年10月11日
 *      Author: redchenjs
 */
#include "gpio.h"

void gpio_init(void)
{
	P1DIR = 0x00;
//	P1REN = 0xff;
	P1OUT = 0x00;

	P2DIR = 0x00;
//	P2REN = 0xff;
	P2OUT = 0x00;

	P3DIR = 0x00;
//	P3REN = 0xff;
	P3OUT = 0x00;

//	P4DIR = 0x00;
//	P4REN = 0xff;
//	P4OUT = 0x00;
//
//	P5DIR = 0x00;
//	P5REN = 0xff;
//	P5OUT = 0x00;
//
//	P6DIR = 0x00;
//	P6REN = 0xff;
//	P6OUT = 0x00;
//
//	P7DIR = 0x00;
//	P7REN = 0xff;
//	P7OUT = 0x00;
//
//	P8DIR = 0x00;
//	P8REN = 0xff;
//	P8OUT = 0x00;
}

void gpio_pinMode(uint8_t pin, uint8_t mode)
{
	uint8_t pin_set = 1 << (pin%10);

	switch (mode) {
		case INPUT:
			switch (pin/10) {
				case 1: P1DIR &=~pin_set; break;
				case 2: P2DIR &=~pin_set; break;
				case 3: P3DIR &=~pin_set; break;
//				case 4: P4DIR &=~pin_set; break;
//				case 5: P5DIR &=~pin_set; break;
//				case 6: P6DIR &=~pin_set; break;
//				case 7: P7DIR &=~pin_set; break;
//				case 8: P8DIR &=~pin_set; break;
				default: break;
			}
			break;
		case OUTPUT:
			switch (pin/10) {
				case 1: P1DIR |= pin_set; break;
				case 2: P2DIR |= pin_set; break;
				case 3: P3DIR |= pin_set; break;
//				case 4: P4DIR |= pin_set; break;
//				case 5: P5DIR |= pin_set; break;
//				case 6: P6DIR |= pin_set; break;
//				case 7: P7DIR |= pin_set; break;
//				case 8: P8DIR |= pin_set; break;
				default: break;
			}
			break;
		case INPUT_PULLUP:
			switch (pin/10) {
				case 1: P1DIR &=~pin_set; P1REN |= pin_set; P1OUT |= pin_set; break;
				case 2: P2DIR &=~pin_set; P2REN |= pin_set; P2OUT |= pin_set; break;
				case 3: P3DIR &=~pin_set; P3REN |= pin_set; P3OUT |= pin_set; break;
//				case 4: P4DIR &=~pin_set; P4REN |= pin_set; P4OUT |= pin_set; break;
//				case 5: P5DIR &=~pin_set; P5REN |= pin_set; P5OUT |= pin_set; break;
//				case 6: P6DIR &=~pin_set; P6REN |= pin_set; P6OUT |= pin_set; break;
//				case 7: P7DIR &=~pin_set; P7REN |= pin_set; P7OUT |= pin_set; break;
//				case 8: P8DIR &=~pin_set; P8REN |= pin_set; P8OUT |= pin_set; break;
				default: break;
			}
			break;
		case INPUT_PULLDOWN:
			switch (pin/10) {
				case 1: P1DIR &=~pin_set; P1REN |= pin_set; P1OUT &=~pin_set; break;
				case 2: P2DIR &=~pin_set; P2REN |= pin_set; P2OUT &=~pin_set; break;
				case 3: P3DIR &=~pin_set; P3REN |= pin_set; P3OUT &=~pin_set; break;
//				case 4: P4DIR &=~pin_set; P4REN |= pin_set; P4OUT &=~pin_set; break;
//				case 5: P5DIR &=~pin_set; P5REN |= pin_set; P5OUT &=~pin_set; break;
//				case 6: P6DIR &=~pin_set; P6REN |= pin_set; P6OUT &=~pin_set; break;
//				case 7: P7DIR &=~pin_set; P7REN |= pin_set; P7OUT &=~pin_set; break;
//				case 8: P8DIR &=~pin_set; P8REN |= pin_set; P8OUT &=~pin_set; break;
				default: break;
			}
			break;
		default: break;
	}
}

void gpio_digitalWrite(uint8_t pin, uint8_t value)
{
	uint8_t pin_set = 1 << (pin%10);

	switch (value) {
		case LOW:
			switch (pin/10) {
				case 1: P1OUT &=~pin_set; break;
				case 2: P2OUT &=~pin_set; break;
				case 3: P3OUT &=~pin_set; break;
//				case 4: P4OUT &=~pin_set; break;
//				case 5: P5OUT &=~pin_set; break;
//				case 6: P6OUT &=~pin_set; break;
//				case 7: P7OUT &=~pin_set; break;
//				case 8: P8OUT &=~pin_set; break;
				default: break;
			}
			break;
		case HIGH:
			switch (pin/10) {
				case 1: P1OUT |= pin_set; break;
				case 2: P2OUT |= pin_set; break;
				case 3: P3OUT |= pin_set; break;
//				case 4: P4OUT |= pin_set; break;
//				case 5: P5OUT |= pin_set; break;
//				case 6: P6OUT |= pin_set; break;
//				case 7: P7OUT |= pin_set; break;
//				case 8: P8OUT |= pin_set; break;
				default: break;
			}
			break;
		default: break;
	}
}
