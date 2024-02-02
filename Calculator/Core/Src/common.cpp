/*
 * common.c
 *
 *  Created on: Nov 18, 2023
 *      Author: zhiyuan
 */

#include <common.hpp>

static uint32_t CLK_PER_US;
static uint32_t CLK_PER_MS;

#ifdef __cplusplus
extern "C" {
#endif

void initDelay(){
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK_DIV8);
	CLK_PER_US = SystemCoreClock / 8 / 1000000;
	CLK_PER_MS = CLK_PER_US * 1000;
}

void delayUSecs(uint32_t us){
	uint32_t temp;
	SysTick -> LOAD = us * CLK_PER_US;		        //设置重装载值
	SysTick -> VAL |= 0x00;		                    //将定时器归零
	SysTick -> CTRL |= SysTick_CTRL_ENABLE_Msk;		//开启定时器

	do{
		temp = SysTick -> CTRL;
	}while(temp & SysTick_CTRL_ENABLE_Msk && !(temp & SysTick_CTRL_COUNTFLAG_Msk));
	SysTick -> CTRL &= ~SysTick_CTRL_ENABLE_Msk;	//关闭定时器
	SysTick -> VAL |= 0x00;		                    //将定时器归零
}

void delayMSecs(uint32_t ms){
	uint32_t temp;
	SysTick -> LOAD = ms * CLK_PER_MS;
	SysTick -> VAL |= 0x00;
	SysTick -> CTRL |= SysTick_CTRL_ENABLE_Msk;

	do{
		temp = SysTick -> CTRL;
	}while(temp & SysTick_CTRL_ENABLE_Msk && !(temp & SysTick_CTRL_COUNTFLAG_Msk));
	SysTick -> CTRL &= ~SysTick_CTRL_ENABLE_Msk;
	SysTick -> VAL |= 0x00;
}


void keepUSBVisable(){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	/* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOA_CLK_ENABLE();
	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
	/*Configure GPIO pin : PA12 */
	GPIO_InitStruct.Pin = GPIO_PIN_12;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
	HAL_Delay(65);
	//先把PA12拉低再拉高，利用D+模拟USB的拔插动作
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
	HAL_Delay(65);
}


#ifdef __cplusplus
}
#endif

std::vector<std::string> Log::msgBuffer;

void Log::sendStringViaCDC(const std::string& message) {
    const char* cMessage = message.c_str();
    uint16_t len = strlen(cMessage);
    CDC_Transmit_FS((uint8_t*)cMessage, len);
}

void Log::addMsg(std::string msg){
	msgBuffer.push_back(msg);
}

void Log::clrMsg(char flag){
	if(flag == 'a')
		msgBuffer.clear();
}

void Log::DisplayMsg(){
	for (auto it = msgBuffer.begin(); it != msgBuffer.end(); ++it) {
		sendStringViaCDC(*it);
	}
}
