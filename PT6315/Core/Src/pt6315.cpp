/*
 * pt6315.c
 *
 *  Created on: 2024年6月12日
 *      Author: zhiyuan
 */

#ifndef SRC_PT6315_C_
#define SRC_PT6315_C_

#include "pt6315.hpp"

//command1
/*
 * 显示模式设定
 * 0 0 - - b3 b2 b1 b0
 *
 * b3~b0: 0100 8区域16分隔符
 */
#define SCAN_MODE_8D20S 0b00001000

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


void PT6315::PT6315_SendCMD(uint8_t CMD){
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, &CMD, sizeof(CMD), HAL_MAX_DELAY);
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);
	HAL_Delay(10);
}

void PT6315::PT6315_SendDTA(){
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET);

	uint8_t cmd3 = 0b11000000;
	HAL_SPI_Transmit(&hspi2, &cmd3, 1, HAL_MAX_DELAY);

    uint8_t test = 0b11111111;
	for (int i = 0; i < 12 ; i++){ // test base to 16 segm and 12 grids
		HAL_SPI_Transmit(&hspi2, &test, sizeof(test), HAL_MAX_DELAY);
		HAL_SPI_Transmit(&hspi2, &test, sizeof(test), HAL_MAX_DELAY);
		HAL_SPI_Transmit(&hspi2, &test, sizeof(test), HAL_MAX_DELAY);
		}

	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);
	HAL_Delay(10);
}

void PT6315::PT6315_Init(){
//	HAL_Delay(200);
//	//清空显示寄存器
//	PT6315_SendCMD(WRITE_DTA_TO_DISPLAY);
//	PT6315_SendCMD(SET_ADR_TO_BEGIN);
//	for(int i=0; i<36; i++){
//		PT6315_SendCMD(0b11111111);
//	}
//
//	//设置显示模式
//	PT6315_SendCMD(SCAN_MODE_8D20S);
//	//开启显示
//	PT6315_SendCMD(DISPLAY_ON_HIGH_LIGHT);

	HAL_Delay(200);
	PT6315_SendCMD(0b01000000);
	PT6315_SendCMD(0b11000000);


	PT6315_SendCMD(0b00000100);
	PT6315_SendCMD(0b10001111);

}

void PT6315::PT6315_Test(){
	PT6315_SendCMD(0b01000000);
	PT6315_SendDTA();
	PT6315_SendCMD(0b00000100);
	PT6315_SendCMD(0b10001111);
}

#endif /* SRC_PT6315_C_ */