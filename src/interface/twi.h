#ifndef i2c_h
#define i2c_h
#include "../system/config.h"
/*
 * ---------I2C---------
 * PORT		TYPE	PIN
 * SCL		OUT		P1.0
 * SDA		INOUT	P1.7
 * ---------------------
 */
#define I2C_PIN_SET 		P1DIR &=~BIT0; P1DIR &=~BIT7

#define I2C_CLK_HIGH 		P1DIR &=~BIT0
#define I2C_CLK_LOW 		P1DIR |= BIT0; P1OUT &=~BIT0

#define I2C_DATA_HIGH 		P1DIR &=~BIT7
#define I2C_DATA_LOW 		P1DIR |= BIT7; P1OUT &=~BIT7

#define I2C_DATA_IN			P1IN  &  BIT7

#ifndef I2C_FREQ
#define I2C_FREQ 100000L
#endif

#ifndef I2C_BUFFER_LENGTH
#define I2C_BUFFER_LENGTH 32
#endif

#define I2C_READ  1
#define I2C_WRITE 0

#define I2C_READY 0
#define I2C_MRX   1
#define I2C_MTX   2
#define I2C_SRX   3
#define I2C_STX   4

void i2c_init(void);
void i2c_disable(void);
void i2c_setAddress(uint8_t);
void i2c_setFrequency(uint32_t);
uint8_t i2c_readFrom(uint8_t, uint8_t*, uint8_t, uint8_t);
uint8_t i2c_writeTo(uint8_t, uint8_t*, uint8_t, uint8_t, uint8_t);
uint8_t i2c_transmit(const uint8_t*, uint8_t);
void i2c_attachSlaveRxEvent( void (*)(uint8_t*, int) );
void i2c_attachSlaveTxEvent( void (*)(void) );
void i2c_reply(uint8_t);
void i2c_start(void);
void i2c_stop(void);
void i2c_releaseBus(void);
void i2c_sendChar(unsigned char data);
unsigned char i2c_getChar(void);

#endif

