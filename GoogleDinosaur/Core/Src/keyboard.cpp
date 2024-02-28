/*
 * keyboard.cpp
 *
 *  Created on: 2024年2月26日
 *      Author: zhiyuan
 */


#include "keyboard.hpp"

void KeyBoard::keyPressed(uint8_t keyCode){
	PressedKey.push_back(keyCode);
}

void KeyBoard::keyboardConfigSwitchTo(std::string configName){
	auto it = MapConfigs.find(configName);
	if(it!=MapConfigs.end())
		KeyBoardMap = it->second;
}

std::vector<uint8_t> KeyBoard::getFuncCode(){
	std::vector<uint8_t>FuncCode;
	for(uint8_t key : PressedKey){
		auto it = KeyBoardMap.find(key);
		if(it!=KeyBoardMap.end())
			FuncCode.push_back(it->second);
	}
	PressedKey.clear();
	return FuncCode;
}

