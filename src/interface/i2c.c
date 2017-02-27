#include <msp430g2553.h>
/*
 * ---------I2C---------
 * PORT		TYPE	PIN
 * SCL		OUT		P3.0
 * SDA		INOUT	P3.1
 * ---------------------
 */
#define I2C_SCL_HIGH	P3DIR &=~BIT0
#define I2C_SCL_LOW		P3DIR |= BIT0
#define I2C_SDA_HIGH	P3DIR &=~BIT1
#define I2C_SDA_LOW		P3DIR |= BIT1
#define I2C_SDA_IN		P3IN  &  BIT1

#define F_CPU 16000000

static inline void delay_us(void)
{
	__delay_cycles(F_CPU/200000);
}

void i2c_init(void)
{
	P3DIR &=~BIT0;
	P3OUT &=~BIT0;
	P3DIR &=~BIT1;
	P3OUT &=~BIT1;
}

void i2c_start(void)
{
	I2C_SDA_HIGH;
	delay_us();
	I2C_SCL_HIGH;
	delay_us();
	I2C_SDA_LOW;
	delay_us();
	I2C_SCL_LOW;
}

void i2c_stop(void)
{
	I2C_SDA_LOW;
	delay_us();
	I2C_SCL_HIGH;
	delay_us();
	I2C_SDA_HIGH;
}

void i2c_transmit_ack(unsigned char ack)
{
	if (ack) {
		I2C_SDA_LOW;
	}
	else {
		I2C_SDA_HIGH;
	}
	delay_us();
	I2C_SCL_HIGH;
	delay_us();
	I2C_SCL_LOW;
}

unsigned char i2c_receive_ack(void)
{
	unsigned char temp;

	I2C_SDA_HIGH;
	delay_us();
	I2C_SCL_HIGH;
	temp = I2C_SDA_IN;
	delay_us();
	I2C_SCL_LOW;

	return temp;
}

void i2c_transmit_char(unsigned char data)
{
	unsigned char i=0;
	for (i=8; i>0; i--) {
		if (data & BIT7) {
			I2C_SDA_HIGH;
		}
		else {
			I2C_SDA_LOW;
		}
		data <<= 1;
		delay_us();
		I2C_SCL_HIGH;
		delay_us();
		I2C_SCL_LOW;
	}
	i2c_receive_ack();
}

unsigned char i2c_receive_char(unsigned char ack)
{
	unsigned char i=0;
	unsigned char temp=0;
	I2C_SDA_HIGH;
	for (i=8; i>0; i--) {
		delay_us();
		I2C_SCL_HIGH;
		temp = temp<<1;
		if (I2C_SDA_IN) temp |= BIT0;
		delay_us();
		I2C_SCL_LOW;
	}
	i2c_transmit_ack(ack);
	return temp;
}

unsigned char i2c_transmit_frame(unsigned char slave_addr, unsigned char *p_buff, unsigned char num)
{
	unsigned char i=0;
	__disable_interrupt();
	i2c_start();
	i2c_transmit_char(slave_addr<<1);		//先发送器件地址和写标志
	for (i=num; i>0; i--) {
		i2c_transmit_char(*p_buff);
		p_buff++;
	}
	i2c_stop();
	__enable_interrupt();
	return 1;
}

unsigned char i2c_receive_frame(unsigned char slave_addr, unsigned char *p_buff, unsigned char num)
{
	unsigned char i=0;
	__disable_interrupt();
	i2c_start();
	i2c_transmit_char((slave_addr<<1) + 0x01);		//先发送器件地址和读标志
	for (i=num; i>0; i--) {
		*p_buff=i2c_receive_char(i-1);
		p_buff++;
	}
	i2c_stop();
	__enable_interrupt();
	return 1;
}
