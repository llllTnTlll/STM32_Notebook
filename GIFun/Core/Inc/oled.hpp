/*
 * oled.hpp
 *
 *  Created on: Jan 24, 2024
 *      Author: zhiyuan
 */

#ifndef INC_OLED_HPP_
#define INC_OLED_HPP_

#include <cstring>
#include <vector>
#include "i2c.h"
#include "font.h"
#include "delay.h"
#include "cdc_usb.h"

// OLED器件地址
#define OLED_ADDRESS 0x78

// OLED参数
#define OLED_PAGE 8            // OLED页数
#define OLED_ROW 8 * OLED_PAGE // OLED行数
#define OLED_COLUMN 128        // OLED列数

extern bool IsDMAAvailable;

// SSD1315寻址模式
enum ADDRESSING_MODE{
	HORIZENTAL_MODE = 0,
	PAGE_MODE = 1,
};

// OLED工作源
enum SIGNAL_SOURCE{
	FROM_USB = 0,
	FROM_MCU = 1,
};

typedef enum {
  OLED_COLOR_NORMAL = 0, // 正常模式 黑底白字
  OLED_COLOR_REVERSED = 1   // 反色模式 白底黑字
} OLED_ColorMode;

class SSD1315{
private:
	ADDRESSING_MODE MODE_NOW = PAGE_MODE;
	SIGNAL_SOURCE SOURCE_NOW = FROM_MCU;

	uint16_t OLED_FRAME_RATE = 0;                      // 当前OLED帧数值

	uint8_t OLED_GRAM[OLED_PAGE][OLED_COLUMN] = {0};   // 显示缓存

	// 用于初始化SSD1315的基本命令（不包括寻址模式指定）
	std::vector<uint8_t> OLED_INIT_CMD =
	{
		0xae,
		0xd5, 0x80,
		0xa8, 0x3f,
		0xd3, 0x00,
		0x40,
		0xa1,
		0xc8,
		0xda, 0x12,
		0x81, 0x66,
		0xd9, 0xf1,
		0xd8, 0x30,
		0xa4,
		0xa6,
		0x8d, 0x14,
		0xaf,
	};
	void SendCMD_DMA(uint8_t *cmd, uint8_t len);
	void SendDTA_DMA(uint8_t *cmd, uint32_t len);

	void OLED_SetPixel(uint8_t x, uint8_t y, OLED_ColorMode color);
	void OLED_SetByte_Fine(uint8_t page, uint8_t column, uint8_t data, uint8_t start, uint8_t end, OLED_ColorMode color);
	void OLED_SetByte(uint8_t page, uint8_t column, uint8_t data, OLED_ColorMode color);
	void OLED_SetBits_Fine(uint8_t x, uint8_t y, uint8_t data, uint8_t len, OLED_ColorMode color);
	void OLED_SetBits(uint8_t x, uint8_t y, uint8_t data, OLED_ColorMode color);
	void OLED_SetBlock(uint8_t x, uint8_t y, const uint8_t *data, uint8_t w, uint8_t h, OLED_ColorMode color);

	void OLED_Init(ADDRESSING_MODE mode);

	uint8_t _OLED_GetUTF8Len(char *string);
public:
	SSD1315(ADDRESSING_MODE mode){
		OLED_Init(mode);
	}
	void ShowFrame();
	void ClearFrame();

	void TestScreen();

	void SwitchAdrMode(ADDRESSING_MODE mode);
	void USBSignalMode(bool isUSBMode);

	void OLED_DrawImage(uint8_t x, uint8_t y, const Image *img, OLED_ColorMode color);
	void OLED_DrawCircle(uint8_t x, uint8_t y, uint8_t r, OLED_ColorMode color);
	void OLED_DrawFilledCircle(uint8_t x, uint8_t y, uint8_t r, OLED_ColorMode color);

	void OLED_PrintASCIIChar(uint8_t x, uint8_t y, char ch, const ASCIIFont *font, OLED_ColorMode color);
	void OLED_PrintASCIIString(uint8_t x, uint8_t y, char *str, const ASCIIFont *font, OLED_ColorMode color);
	void OLED_PrintString(uint8_t x, uint8_t y, char *str, const Font *font, OLED_ColorMode color);

};

#endif /* INC_OLED_HPP_ */
