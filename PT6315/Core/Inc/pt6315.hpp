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

/*
 * 芯片基本特性（坑）
 * LSB CPOL->hight CPHA->2edge
 * 传输速度<1000kbits/s
 * 注意发送数据时的片选信号，传输数据时要一直拉低
 */

//command1
/*
 * 显示模式设定
 * 0 0 - - b3 b2 b1 b0
 *
 * b3~b0: 0100 8区域16分隔符
 */
#define SCAN_MODE_8D20S 0b00000010

//command2
/*
 * 数据设置命令
 * 0 1 - - b3 b2 b1 b0
 *
 * b3: 0 for 普通模式
 *     1 for 测试模式
 *
 * b2: 0 for 地址自增
 *     1 for 指定地址
 *
 * b1&b0: 00 向显示器寄存器写数据
 *        01 向驱动芯片LED写数据
 *        10 读取矩阵键盘数据
 *        11 无效
 *
 */
#define WRITE_DTA_TO_DISPLAY 0b01000000

//command3
/*
 * 地址设置模式
 * 1 1 b5 b4 b3 b2 b1 b0
 *
 * b5-b0 地址
 */
#define SET_ADR_TO_BEGIN 0b11000000

//command4
/*
 * 显示开关与亮度
 * 1 0 - - b3 b2 b1 b0
 *
 * b3 for 开关显示
 * b2~b0: 显示亮度
 */
#define DISPLAY_ON_HIGH_LIGHT 0b10001111
#define DISPLAY_OFF_MID_LIGHT 0b10000100


//GRID1
#define G1_DVD 0b10000000
#define V 0b00100000

//数字
#define NUM1 0b00100100
#define NUM2 0b01101011
#define NUM3 0b01101101
#define NUM4 0b00111100
#define NUM5 0b01011101
#define NUM6 0b01011111
#define NUM7 0b01100100
#define NUM8 0b01111111
#define NUM9 0b01111101
#define NUM0 0b01110111

class PT6315{
private:
	uint8_t VFD_GRID = 6;
	uint8_t VFD_SEG = 16;

	uint8_t* BUFFER;
	uint8_t BUFFER_SIZE = 0;

	void PT6315_SendCMD(uint8_t CMD);
	void PT6315_SendDTA(uint8_t* sendBuf, uint8_t len);
	void PT6315_Init();
public:
	PT6315(){
		// 输出缓存初始化
		BUFFER_SIZE = VFD_GRID * 3;
		BUFFER = new uint8_t[BUFFER_SIZE];
		for(int i=0; i<BUFFER_SIZE; i++){
			BUFFER[i] = 0b00000000;
		}
		// 芯片初始化
		PT6315_Init();
	}
	void PT6315_Test();
	void PT6315_Clear();
	void PT6315_ShowNums();
};

#endif /* INC_PT6315_HPP_ */
