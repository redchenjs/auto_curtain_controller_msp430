/*
 * gpio.h
 *
 *  Created on: 2016年10月11日
 *      Author: redchenjs
 */
#ifndef SRC_GPIO_H_
#define SRC_GPIO_H_
#include "../system/config.h"

void gpio_init(void);
void gpio_pinMode(uint8_t pin, uint8_t mode);
void gpio_digitalWrite(uint8_t pin, uint8_t value);

#endif /* SRC_GPIO_H_ */
