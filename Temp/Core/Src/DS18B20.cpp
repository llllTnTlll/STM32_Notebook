/*
 * DS18B20.cpp
 *
 *  Created on: Jan 13, 2024
 *      Author: zhiyuan
 */

# include "DS18B20.hpp"

void DS18B20::DQ(bool pinState){
	if(pinState)
		HAL_GPIO_WritePin(DQ_Port, DQ_Pin, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(DQ_Port, DQ_Pin, GPIO_PIN_RESET);
}

void DS18B20::SwitchMode(uint8_t mode){
	//mode 1-->output
	//mode 0-->input

	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.Speed =  GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Pin = DQ_Pin;

	if(mode == 1){
		GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStructure.Pull = GPIO_NOPULL;
	}
	else if(mode == 0){
		GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
		GPIO_InitStructure.Pull = GPIO_PULLUP;
	}

	HAL_GPIO_Init(DQ_Port, &GPIO_InitStructure);
}

bool DS18B20::Ping(){
	SwitchMode(1);
	DQ(1);
	delayUSecs(5);
	DQ(0);
	delayUSecs(700);
	DQ(1);
	delayUSecs(60);
	SwitchMode(0);

	if(HAL_GPIO_ReadPin(DQ_Port, DQ_Pin) == GPIO_PIN_RESET){
		delayUSecs(240);
		if(HAL_GPIO_ReadPin(DQ_Port, DQ_Pin) == GPIO_PIN_SET)
			return true;
		else
			return false;
	}
	else
		return false;
}


void DS18B20::WriteByte(uint8_t cmd){
	SwitchMode(1);
	for(int i=0; i<8; i++){
		DQ(0);
		delayUSecs(2);
		DQ(cmd&0x01);
		delayUSecs(60);
		DQ(1);
		cmd >>= 1;
		delayUSecs(2);
	}
}

uint8_t DS18B20::ReadByte(){
	uint8_t data = 0;
	for(int i=0; i<8; i++){
		SwitchMode(1);
		DQ(0);
		delayUSecs(2);
		DQ(1);
		SwitchMode(0);
		delayUSecs(10);
		data >>= 1;
		if(HAL_GPIO_ReadPin(DQ_Port, DQ_Pin) == GPIO_PIN_SET)
			data |= 0x80;
		delayUSecs(60);
		DQ(1);
	}
	return data;
}

uint16_t DS18B20::GetTemp(){
	uint8_t dataLow;
	uint8_t dataHigh;
	uint16_t data;

	Ping();
	WriteByte(0xCC);
	WriteByte(0x44);

	while(ReadByte()!=0xFF){};

	Ping();
	WriteByte(0xCC);
	WriteByte(0xBE);

	dataLow = ReadByte();
	dataHigh = ReadByte();
	data = dataLow|(dataHigh<<8);

	return data;
}
