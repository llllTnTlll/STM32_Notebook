/*
 * logic_core.c
 *
 *  Created on: Jan 31, 2024
 *      Author: zhiyuan
 */

#include "logic_core.hpp"

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
		oled->OLED_DrawImage(obj->getLocationX(), obj->getLocationY(), obj->getHexImg(), OLED_COLOR_NORMAL, COVER);
	}
	for(GameObj* obj : foregroundObjs){
		oled->OLED_DrawImage(obj->getLocationX(), obj->getLocationY(), obj->getHexImg(), OLED_COLOR_NORMAL, OVERLAY);
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
	if(rand->withXPercentProbability(20)){
		SPEED_MODE speed[2] = {static_cast<SPEED_MODE>(rand->getRandomInt16(3, 4)), STATIC};
		uint8_t loc[2] = {OLED_COLUMN, static_cast<uint8_t>(rand->getRandomInt16(8, 20))};
		Cloud *cloud = new Cloud(loc, speed);
		backgroundObjs.push_back(cloud);
	}
	//百分之50的概率生成一个仙人掌
	if(rand->withXPercentProbability(50)){
		Cactus *cactus = new Cactus();
		foregroundObjs.push_back(cactus);
	}
	//百分之50的概率变速
	if(rand->withXPercentProbability(50)){
		Cactus::setSpeedALL(static_cast<SPEED_MODE>(rand->getRandomInt16(0, 4)), STATIC);
	}
}
