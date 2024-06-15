/*
 * pt6315.c
 *
 *  Created on: 2024年6月12日
 *      Author: zhiyuan
 */

#ifndef SRC_PT6315_C_
#define SRC_PT6315_C_

#include "pt6315.hpp"


void PT6315::PT6315_SendCMD(uint8_t CMD){
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, &CMD, sizeof(CMD), HAL_MAX_DELAY);
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);
	HAL_Delay(10);
}

void PT6315::PT6315_SendDTA(uint8_t* sendBuf, uint8_t len){
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET);

	uint8_t cmd3 = SET_ADR_TO_BEGIN;
	HAL_SPI_Transmit(&hspi2, &cmd3, 1, HAL_MAX_DELAY);

	for (int i = 0; i < len ; i++){
		HAL_SPI_Transmit(&hspi2, sendBuf, len, HAL_MAX_DELAY);
	}

	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);
	HAL_Delay(10);
}

void PT6315::PT6315_Init(){
	HAL_Delay(200);
	PT6315_Clear();

	PT6315_SendCMD(SCAN_MODE_8D20S);
	PT6315_SendCMD(DISPLAY_ON_HIGH_LIGHT);

}

void PT6315::PT6315_ShowNums(){
	BUFFER[7] = NUM0;
	BUFFER[9] = NUM1;
	BUFFER[10] = NUM2;
	BUFFER[12] = NUM3;
	BUFFER[13] = NUM4;
	BUFFER[15] = NUM5;
	BUFFER[16] = NUM6;
	PT6315::PT6315_SendDTA(BUFFER, BUFFER_SIZE);
}

void PT6315::PT6315_Test(){
	PT6315_SendCMD(WRITE_DTA_TO_DISPLAY);
	uint8_t buf[36] = {0};
	for(int i=0; i<36; i++){
		buf[i] = 0b11111111;
	}
	PT6315_SendDTA(buf, 36);
	PT6315_SendCMD(SCAN_MODE_8D20S);
	PT6315_SendCMD(DISPLAY_ON_HIGH_LIGHT);
}

void PT6315::PT6315_Clear(){
	PT6315_SendCMD(WRITE_DTA_TO_DISPLAY);
	uint8_t buf[36] = {0};
	PT6315_SendDTA(buf, 36);
}

#endif /* SRC_PT6315_C_ */
