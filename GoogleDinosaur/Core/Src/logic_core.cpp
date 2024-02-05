/*
 * logic_core.c
 *
 *  Created on: Jan 31, 2024
 *      Author: zhiyuan
 */

#include "logic_core.hpp"


bool LogicCore::withXPercentProbability(uint8_t prob){
	if(randomInt16(0, 100) <= prob)
		return true;
	return false;
}

int16_t LogicCore::randomInt16(int16_t begin, int16_t end){
	std::uniform_int_distribution<int16_t> dis(begin, end);
	return dis(gen);
}

void LogicCore::renewAll(){
	for(GameObj* obj : backgroundObjs){
		obj->recalcuProperties();
	}
	for(GameObj* obj : foregroundObjs){
		obj->recalcuProperties();
	}
}

void LogicCore::drawAll(){
	for(GameObj* obj : backgroundObjs){
		oled->OLED_DrawImage(obj->getLocationX(), obj->getLocationY(), obj->getHexImg(), OLED_COLOR_NORMAL);
	}
	for(GameObj* obj : foregroundObjs){
		oled->OLED_DrawImage(obj->getLocationX(), obj->getLocationY(), obj->getHexImg(), OLED_COLOR_NORMAL);
	}
}

void LogicCore::checkAll(){
	//清除所有失效对象
	backgroundObjs.erase(std::remove_if(backgroundObjs.begin(), backgroundObjs.end(),
	                        [](GameObj* obj) { return obj->getReclaimFlag(); }),
	                        backgroundObjs.end());
	foregroundObjs.erase(std::remove_if(foregroundObjs.begin(), foregroundObjs.end(),
		                    [](GameObj* obj) { return obj->getReclaimFlag(); }),
		                    foregroundObjs.end());

	//百分之20的概率生成一朵云
	if(withXPercentProbability(20)){
		int16_t speed[2] = {randomInt16(-40, -30), 0};
		uint8_t loc[2] = {OLED_COLUMN, static_cast<uint8_t>(randomInt16(8, 20))};
		Cloud *cloud = new Cloud(loc, speed);
		backgroundObjs.push_back(cloud);
	}
}
