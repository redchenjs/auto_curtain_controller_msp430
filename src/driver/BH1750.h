/*
 * BH1750.h
 *
 *  Created on: 2016年10月20日
 *      Author: redchenjs
 */


#ifndef BH1750_h
#define BH1750_h

#include "../system/config.h"

class BH1750 {
	public:
		BH1750();
		void getLux(uint16_t& illuminance);

	private:
};

#endif

