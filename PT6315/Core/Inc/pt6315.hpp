/*
 * pt6315.hpp
 *
 *  Created on: Jun 12, 2024
 *      Author: zhiyuan
 */

#ifndef INC_PT6315_HPP_
#define INC_PT6315_HPP_


#include "stm32f1xx_hal.h"
#include "spi.h"
#include <vector>
#include <string>
#include <map>

class PT6315{
private:
	uint8_t VFD_GRID = 8;
	uint8_t VFD_SEG = 16;

	void PT6315_SendCMD(uint8_t CMD);
	void PT6315_SendDTA(uint8_t* sendBuf, uint8_t len);
	void PT6315_Init();
public:
	PT6315(){
		PT6315_Init();
	}
	void PT6315_Test();
	void PT6315_Clear();
};

#endif /* INC_PT6315_HPP_ */
