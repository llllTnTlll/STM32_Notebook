/*
 * DS18B20.hpp
 *
 *  Created on: Jan 13, 2024
 *      Author: zhiyuan
 */

#ifndef INC_DS18B20_HPP_
#define INC_DS18B20_HPP_

#include "main.h"
#include "delay.h"

class DS18B20{
private:
	GPIO_TypeDef * DQ_Port;
	uint16_t DQ_Pin;

	void DQ(bool mode);
	void SwitchMode(uint8_t mode);
	void WriteByte(uint8_t cmd);
	uint8_t ReadByte();
public:
	DS18B20(){
		DQ_Port = DS18B20_DQ_GPIO_Port;
		DQ_Pin = DS18B20_DQ_Pin;
	}
	bool Ping();
	uint16_t GetTemp();
};

#endif /* INC_DS18B20_HPP_ */
