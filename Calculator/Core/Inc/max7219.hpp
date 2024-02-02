/*
 * max7219.hpp
 *
 *  Created on: Nov 16, 2023
 *      Author: zhiyuan
 */

#ifndef INC_MAX7219_HPP_
#define INC_MAX7219_HPP_

#define MAX7219_SPI hspi1
#define TRANSMIT_OVERTIME 1000

//寄存器地址
#define NO_OP              0x00
#define DIGIT0             0x01
#define DIGIT1             0x02
#define DIGIT2             0x03
#define DIGIT3             0x04
#define DIGIT4             0x05
#define DIGIT5             0x06
#define DIGIT6             0x07
#define DIGIT7             0x08
#define DECODE_MODE        0x09
#define INTENSITY          0x0A
#define SCAN_LIMIT         0x0B
#define SHUT_DOWN          0x0C
#define DISPLAY_TEST       0x0F

//译码模式
#define DECODE_D0_D7       0xFF

#include "spi.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_spi.h"
#include <common.hpp>
#include <string>

class MAX7219{
private:
	void max7219Send(uint8_t address,uint8_t data);
public:
	void max7219Init();
	void setTestMode(bool status);
	void setDecodeMode(uint8_t mode);
	void setBrightness(uint8_t level);
	void setWorkMode(bool status);
	void setScanMode(uint8_t mode);
	void clrScreen();
	void blinkScreen();
	void refreshScreen(std::string s);
};

#endif /* INC_MAX7219_HPP_ */
