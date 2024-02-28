/*
 * logic_core.c
 *
 *  Created on: Jan 31, 2024
 *      Author: zhiyuan
 */

#include "logic_core.hpp"

struct Rectangle {
    uint8_t x1, y1;         // 左上角坐标
    uint8_t width, height;  // 宽度和高度
};

bool isIntersect(const Rectangle& rect1, const Rectangle& rect2) {
	uint8_t x_overlap = std::max(0, std::min(rect1.x1 + rect1.width, rect2.x1 + rect2.width) - std::max(rect1.x1, rect2.x1));
    uint8_t y_overlap = std::max(0, std::min(rect1.y1 + rect1.height, rect2.y1 + rect2.height) - std::max(rect1.y1, rect2.y1));
    return (x_overlap > 0 && y_overlap > 0);
}

Rectangle getIntersectBox(std::shared_ptr<GameObj> obj){
	Rectangle r = {obj->getLocationX(),
			       obj->getLocationY(),
				   obj->getWidth(),
				   obj->getHeight(),
	};
	return r;
}

bool LogicCore::isGameOver(){
	// 放点水
	Rectangle r1 = {(uint8_t)(mainCharactor->getLocationX()+10),
			        mainCharactor->getLocationY(),
					(uint8_t)(mainCharactor->getWidth()-10),
					(uint8_t)(mainCharactor->getHeight()-5),
	};

	for(const std::shared_ptr<GameObj>& obj : foregroundObjs){
		Rectangle r2 = getIntersectBox(obj);
		if(isIntersect(r1, r2))
			return true;
	}
	return false;
}

void LogicCore::renewGenerateFlag(){
	uint8_t CactusNum = 0;
	uint8_t CloudNum = 0;

	for(const std::shared_ptr<GameObj>& obj : backgroundObjs){
		std::string tname = obj->getObjType();
		if(tname == "Cloud")
			CloudNum++;
	}
	for(const std::shared_ptr<GameObj>& obj : foregroundObjs){
		std::string tname = obj->getObjType();
		if(tname == "Cactus")
			CactusNum++;
	}
	CactusNum<MaxCactusNum ? shouldGenerateCactus=true : shouldGenerateCactus=false;
	CloudNum<MaxCloudNum ? shouldGenerateCloud=true : shouldGenerateCloud=false;
}

void LogicCore::updateTotalScore(){
	if(Score<9999)
		Score++;
}

std::string LogicCore::getTotalScore(){
	std::string result = "SC:";
	std::string numStr = std::to_string(Score);
	uint8_t padding = 4 - numStr.size();

	// 如果需要填充0
	if (padding > 0) {
	    result.append(padding, '0');
	}

	// 添加数字字符串
	result += numStr;

	return result;
}

void LogicCore::renewAll(){
	// 按键响应
	std::vector FuncCode = keyboard->getFuncCode();
	for(uint8_t code : FuncCode){
		switch(code){
		case FUNC_JUMP:
			mainCharactor->jumpUp();
		}
	}

	// 状态更新
	for(const std::shared_ptr<GameObj>& obj : backgroundObjs){
		obj->recalcuProperties();
	}
	for(const std::shared_ptr<GameObj>& obj : foregroundObjs){
		obj->recalcuProperties();
	}
	mainCharactor->recalcuProperties();

	// 碰撞检测
	if(isGameOver())
		Score = 0;
}

void LogicCore::drawAll(){
	// TODO修改绘制逻辑 先画到画布上再统一绘制
	for(const std::shared_ptr<GameObj>& obj : backgroundObjs){
		oled->OLED_DrawImage(obj->getLocationX(), obj->getLocationY(), obj->getHexImg(), OLED_COLOR_NORMAL, COVER);
	}
	for(const std::shared_ptr<GameObj>& obj : foregroundObjs){
		oled->OLED_DrawImage(obj->getLocationX(), obj->getLocationY(), obj->getHexImg(), OLED_COLOR_NORMAL, OVERLAY);
	}
	oled->OLED_DrawImage(mainCharactor->getLocationX(), mainCharactor->getLocationY(), mainCharactor->getHexImg(), OLED_COLOR_NORMAL, OVERLAY);

	// 绘制总分数
	oled->OLED_PrintASCIIString(OLED_COLUMN-42, 1, &getTotalScore()[0], &afont8x6, OLED_COLOR_NORMAL);
}

void LogicCore::checkAll(){
	//清除所有失效对象
	backgroundObjs.erase(std::remove_if(backgroundObjs.begin(), backgroundObjs.end(),
	                        [](const std::shared_ptr<GameObj>& obj) { return obj->getReclaimFlag(); }),
	                        backgroundObjs.end());
	foregroundObjs.erase(std::remove_if(foregroundObjs.begin(), foregroundObjs.end(),
		                    [](const std::shared_ptr<GameObj>& obj){ return obj->getReclaimFlag(); }),
		                    foregroundObjs.end());

	//检查所有对象数量确认是否可以生成新对象
	renewGenerateFlag();

	//百分之10的概率生成一朵云
	if(rand->withXPercentProbability(10)&&shouldGenerateCloud){
		SPEED_MODE speed[2] = {static_cast<SPEED_MODE>(rand->getRandomInt16(3, 4)), STATIC};
		uint8_t loc[2] = {OLED_COLUMN, static_cast<uint8_t>(rand->getRandomInt16(8, 20))};
		std::shared_ptr<Cloud> cloud(new Cloud(loc, speed));
		backgroundObjs.push_back(cloud);
	}
	//百分之10的概率生成一个仙人掌
	if(rand->withXPercentProbability(10)&&shouldGenerateCactus){
		std::shared_ptr<Cactus> cactus(new Cactus());
		foregroundObjs.push_back(cactus);
	}
	//变速
	if(Score <50)
		setGameSpeed(NEGATIVE_SLOW, STATIC);
	if(Score>50 && Score<100)
		setGameSpeed(NEGATIVE_NORMAL, STATIC);
	if(Score>100 && Score<150)
		setGameSpeed(NEGATIVE_FAST, STATIC);
	if(Score>150)
		setGameSpeed(NEGATIVE_SUPER_FAST, STATIC);
}
