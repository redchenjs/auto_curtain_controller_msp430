#ifndef I2C_H_
#define I2C_H_

extern void i2c_init(void);

extern unsigned char i2c_transmit_frame(unsigned char slave_addr, unsigned char *p_buff, unsigned char num);
extern unsigned char i2c_receive_frame(unsigned char slave_addr, unsigned char *p_buff, unsigned char num);

#endif /* I2C_H_ */


