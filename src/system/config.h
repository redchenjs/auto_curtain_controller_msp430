/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _CONFIG_H_
#define _CONFIG_H_

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>	
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

/* Exported types ------------------------------------------------------------*/
typedef unsigned int word;
typedef bool boolean;
typedef uint8_t byte;

/* Exported constants --------------------------------------------------------*/
#define F_CPU 16000000

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105
#define EULER 2.718281828459045235360287471352

#define HIGH 0x1
#define LOW  0x0

#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2
#define INPUT_PULLDOWN 0x3

/* Exported macro ------------------------------------------------------------*/
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define abs(x) ((x)>0?(x):-(x))
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)
#define sq(x) ((x)*(x))

#define clockCyclesPerMicrosecond() ( F_CPU / 1000000L )
#define clockCyclesToMicroseconds(a) ( (a) / clockCyclesPerMicrosecond() )
#define microsecondsToClockCycles(a) ( (a) * clockCyclesPerMicrosecond() )

#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

#define bit(b) (1UL << (b))

/* Exported functions ------------------------------------------------------- */

/*------------------------------------------------------------------------------------------------------*/
//MSP430G2553
#include "msp430g2553.h"
#include "bcs.h"
#include "wdt.h"
#include "delay.h"
#include "timer.h"
#include "gpio.h"
#include "flash.h"

#define irq_enable() _enable_interrupts()
#define irq_disable() _disable_interrupts()

/*------------------------------------------------------------------------------------------------------*/
//init
#include "init.h"
#include "fonts.h"
#include "user.h"

/*------------------------------------------------------------------------------------------------------*/
//Flash
#include "record.h"

/*------------------------------------------------------------------------------------------------------*/
//SPI
#include "spi.h"

#include "SSD1331.h"
#include "display.h"

/*------------------------------------------------------------------------------------------------------*/
//I2C
#include "twi.h"
#include "i2c.h"

#include "BH1750.h"
#include "senser.h"

#include "DS3231.h"
#include "clock.h"

/*------------------------------------------------------------------------------------------------------*/
//Stepper
#include "Stepper.h"
#include "motor.h"

/*------------------------------------------------------------------------------------------------------*/
#endif

/*-------------------------------END OF FILE-------------------------------*/

