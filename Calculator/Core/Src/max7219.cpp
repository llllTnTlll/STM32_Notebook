/*
 * max7219.cpp
 *
 *  Created on: Nov 16, 2023
 *      Author: zhiyuan
 */
# include "max7219.hpp"

void MAX7219::max7219Send(uint8_t address,uint8_t data){
	uint16_t Transmit_buf = (0x00ff&data)|(0xff00&(address<<8));
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&MAX7219_SPI,(uint8_t*)&Transmit_buf,1,TRANSMIT_OVERTIME);
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);
	delayUSecs(500);
}

void MAX7219::max7219Init(){
	//进入正常工作模式
	setWorkMode(true);
	//七位全扫描模式
	setScanMode(0x07);
	//打开译码模式
	setDecodeMode(DECODE_D0_D7);
}

void MAX7219::setBrightness(uint8_t level){
	if(level <= 15)
		max7219Send(INTENSITY, level);
}

void MAX7219::setTestMode(bool status){
	if(status)
		max7219Send(DISPLAY_TEST, 0x01);
	else
		max7219Send(DISPLAY_TEST, 0x00);
}

void MAX7219::setWorkMode(bool status){
	if(status)
		max7219Send(SHUT_DOWN, 1);
	else
		max7219Send(SHUT_DOWN, 0);
}

void MAX7219::setDecodeMode(uint8_t mode){
	max7219Send(DECODE_MODE, mode);
}

void MAX7219::setScanMode(uint8_t mode){
	max7219Send(SCAN_LIMIT, mode);
}

void MAX7219::clrScreen(){
	for(uint8_t reg = 0x01; reg <= 8; reg++){
		max7219Send(reg, 0x0f);
	}
}

void MAX7219::blinkScreen(){
	std::string bink = "--------";
	for(int i = 0; i < 2; i++){
		refreshScreen(bink);
		delayMSecs(200);
		clrScreen();
		delayMSecs(200);
	}
}

void MAX7219::refreshScreen(std::string s){
	bool dpFlag = false;
	uint8_t reg = 0x01;
	uint8_t digitCount = 0;

	clrScreen();
	for (auto it = s.rbegin(); it != s.rend(); ++it) {
		if (std::isdigit(*it)) {
	        if (digitCount < 8) {
	            if (dpFlag) {
	                max7219Send(reg, *it | 0b10000000);
	                dpFlag = false;
	            } else {
	                max7219Send(reg, *it);
	            }
	            reg++;
	            digitCount++;
	        }
	    }
		else if(*it == '-'){
			max7219Send(reg, 10);
			reg++;
			digitCount++;
		}
		else if (*it == '.') {
	    	dpFlag = true;
	    }
	}
}
