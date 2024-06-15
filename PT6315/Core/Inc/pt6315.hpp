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
	std::string OUTPUT_BUFFER;  //当前显示内容

	void PT6315_Init();
public:
	PT6315(){
		PT6315_Init();
	}
	void PT6315_SendCMD(uint8_t CMD);
	void PT6315_SendDTA();
	void PT6315_Test();
};

#endif /* INC_PT6315_HPP_ */
