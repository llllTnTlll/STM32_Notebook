/*
 * cdc_usb.c
 *
 *  Created on: Jan 28, 2024
 *      Author: zhiyuan
 */

#include "cdc_usb.h"

uint8_t RecvDataBuffer[1024] = {0};
uint32_t RecvDataIndex = 0;

uint8_t CheckRecvFlag(uint32_t Len){
	if(RecvDataIndex == Len)
		return 1;
	return 0;
}

void ResetBuffer(){
	memset(RecvDataBuffer, 0, sizeof(RecvDataBuffer));
	RecvDataIndex = 0;
}

void ShakeHand(uint32_t freq){
	while(1){
		if(RecvDataBuffer[0] == SHAKE_HAND_BACK){
			ResetBuffer();
			break;
		}
		TransmitCMD(SHAKE_HAND);
		delayMSecs(freq);
	}
}

void TransmitCMD(USB_CMD cmd){
	uint8_t cmdByte = (uint8_t)cmd;
	CDC_Transmit_FS(&cmdByte, 1);
}

void RecvData(uint32_t Len){
	memset(RecvDataBuffer, 0, sizeof(RecvDataBuffer));
	//等待数据传输完成
	while(!CheckRecvFlag(Len)){};
	//添加数据校验
}
