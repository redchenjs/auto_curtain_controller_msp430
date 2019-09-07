/*
 * i2c.h
 *
 *  Created on: 2016-03-22
 *      Author: Jack Chen <redchenjs@live.com>
 */

#ifndef INC_CHIP_I2C_H_
#define INC_CHIP_I2C_H_

extern void i2c_init(void);

extern unsigned char i2c_transmit_frame(unsigned char slave_addr, unsigned char *p_buff, unsigned char num);
extern unsigned char i2c_receive_frame(unsigned char slave_addr, unsigned char *p_buff, unsigned char num);

#endif /* INC_CHIP_I2C_H_ */
