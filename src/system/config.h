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

#include "../device/bcs.h"
#include "../device/wdt.h"
#include "../device/delay.h"
#include "../device/timer.h"
#include "../device/gpio.h"
#include "../device/flash.h"

#define irq_enable() _enable_interrupts()
#define irq_disable() _disable_interrupts()

/*------------------------------------------------------------------------------------------------------*/
//init
#include "../system/init.h"
#include "../system/fonts.h"
#include "../user/user.h"

/*------------------------------------------------------------------------------------------------------*/
//Flash
#include "../user/record.h"

/*------------------------------------------------------------------------------------------------------*/
//SPI
#include "../interface/spi.h"

#include "../driver/SSD1331.h"
#include "../user/display.h"

/*------------------------------------------------------------------------------------------------------*/
//I2C
#include "../interface/twi.h"
#include "../interface/i2c.h"

#include "../driver/BH1750.h"
#include "../user/senser.h"

#include "../driver/DS3231.h"
#include "../user/clock.h"

/*------------------------------------------------------------------------------------------------------*/
//Stepper
#include "../driver/Stepper.h"
#include "../user/motor.h"

/*------------------------------------------------------------------------------------------------------*/
#endif

/*-------------------------------END OF FILE-------------------------------*/

