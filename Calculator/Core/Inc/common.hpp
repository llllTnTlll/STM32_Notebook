/*
 * common.h
 *
 *  Created on: Nov 18, 2023
 *      Author: zhiyuan
 */

#ifndef INC_COMMON_HPP_
#define INC_COMMON_HPP_

#include <stm32f1xx_hal.h>
#include <string>
#include <vector>
#include "usbd_cdc_if.h"

#ifdef __cplusplus
extern "C" {
#endif

void initDelay();
void delayUSecs(uint32_t us);
void delayMSecs(uint32_t ms);

void keepUSBVisable();

#ifdef __cplusplus
}
#endif

class Log{
private:
//	static void sendStringViaCDC(const std::string& message);
public:
	static void sendStringViaCDC(const std::string& message);
	static std::vector<std::string> msgBuffer;
	static void addMsg(std::string msg);
	static void clrMsg(char flag);
	static void DisplayMsg();
};

#endif /* INC_COMMON_HPP_ */
