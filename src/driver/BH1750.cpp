/*
 * BH1750.cpp
 *
 *  Created on: 2016年10月20日
 *      Author: redchenjs
 */

#include "BH1750.h"

#define BH1750_ADDRESS 0x23
#define ONE_TIME_H_RESOLUTION_MODE 0x20
//One Time H-Resolution Mode:
//Resolution = 1 lux
//Measurement time (max.) = 180ms
//Power down after each measurement

// Constructor
BH1750::BH1750() {
	// nothing to do for this constructor.
}

/*****************************************
	Public Functions
 *****************************************/

void BH1750::getLux(uint16_t& illuminance)
{
	byte highByte = 0, lowByte = 0;

    i2c.beginTransmission(BH1750_ADDRESS); //"notify" the matching device
    i2c.write(ONE_TIME_H_RESOLUTION_MODE);     //set operation mode
    i2c.endTransmission();

    delay_ms(180);

    i2c.requestFrom(BH1750_ADDRESS, 2); //ask device to read back 2 bytes from the sensor
    highByte = i2c.read();  // get the high byte
    lowByte = i2c.read(); // get the low byte

    illuminance = (highByte << 8) | lowByte;
}

