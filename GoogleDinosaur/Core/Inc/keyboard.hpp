/*
 * keyboard.hpp
 *
 *  Created on: 2024年2月26日
 *      Author: zhiyuan
 */

#ifndef INC_KEYBOARD_HPP_
#define INC_KEYBOARD_HPP_

#define KEY_BOARD_A 0
#define KEY_BOARD_B 1

#define FUNC_NONE 0
#define FUNC_JUMP 1

#include <map>
#include <string>
#include <vector>

class KeyBoard{
private:
	// 未响应的按键
	std::vector<uint8_t>PressedKey;

	// 当前应用的按键映射方案
	std::map<uint8_t, uint8_t>KeyBoardMap;

	// 全部按键映射方案
	std::map<std::string, std::map<uint8_t, uint8_t>>MapConfigs;
public:
	KeyBoard(){
		std::map<uint8_t, uint8_t>DinoGameConfig;
		DinoGameConfig[KEY_BOARD_A] = FUNC_JUMP;
		DinoGameConfig[KEY_BOARD_B] = FUNC_NONE;
		MapConfigs["DinoGameConfig"] = DinoGameConfig;

		keyboardConfigSwitchTo("DinoGameConfig");
	}

	void keyboardConfigSwitchTo(std::string configName);
	void keyPressed(uint8_t keyCode);
	std::vector<uint8_t> getFuncCode();
};



#endif /* INC_KEYBOARD_HPP_ */
