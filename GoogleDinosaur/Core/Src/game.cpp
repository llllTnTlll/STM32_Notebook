/*
 * game.cpp
 *
 *  Created on: Jan 31, 2024
 *      Author: zhiyuan
 */
#include "game.hpp"

SPEED_MODE GAME_SPEED[2] = {NEGATIVE_SLOW, STATIC};

std::list<GameObj::speedNode> GameObj::SPEED = {
		{NEGATIVE_SUPER_FAST,1,-3},
		{NEGATIVE_FAST,1,-2},
		{NEGATIVE_NORMAL,1,-1},
		{NEGATIVE_SLOW,2,-1},
		{NEGATIVE_SUPER_SLOW,3,-1},
		{STATIC, 1, 0},
		{POSITIVE_SUPER_SLOW,3,1},
		{POSITIVE_SLOW,2,1},
		{POSITIVE_NORMAL,1,1},
		{POSITIVE_FAST,1,2},
		{POSITIVE_SUPER_FAST,1,3},
};


void GameObj::updateReclaimFlag(){
	if(current_loc[0] > 128 && current_loc[0] < 256-width){
		shouldReclaim = true;
	}
}

void GameObj::initProperties(){
	height = getHexImg()->h;
	width = getHexImg()->w;
}

void GameObj::recalcuProperties(){
	if(!shouldReclaim){
		currentInterval[0]--;
		currentInterval[1]--;
		if(currentInterval[0] == 0)
			takeMove(0);
		if(currentInterval[1] == 0)
			takeMove(1);
	}
	//判断该对象是否已经失效
	updateReclaimFlag();
}

void GameObj::takeMove(uint8_t axisIndex){
	// 加速度是否计算
	if(shouldCacuAcc){
		accIntervalCount[0]--;
		accIntervalCount[1]--;
		if(accIntervalCount[0] == 0)
			speedUpDown(0);
		if(accIntervalCount[1] == 0)
			speedUpDown(1);
	}

	for (const auto& node : SPEED) {
		if (node.mode == static_cast<SPEED_MODE>(speed[axisIndex])){
			// 重设刷新间隔
			currentInterval[axisIndex] = node.interval;
			current_loc[axisIndex] += node.step;
		}
	}
}

void GameObj::speedUpDown(uint8_t axisIndex){
	// 获取指向当前速度的迭代器
	auto it = std::find_if(SPEED.begin(), SPEED.end(), [this, axisIndex](const speedNode& node) {
	        return node.mode == this->speed[axisIndex];
	});
	if(it!=SPEED.end()){
		for(uint8_t i=0; i < std::abs(accStep[axisIndex]); i++){
			if(accStep[axisIndex] > 0 && std::next(it) != SPEED.end())
				it++;
			if(accStep[axisIndex] < 0 && std::prev(it) != SPEED.begin())
				it--;
		}
		speed[axisIndex] = it->mode;
	}
	// 重设间隔
	accIntervalCount[axisIndex] = accInterval[axisIndex];
}

void GameObj::resetAccSys(){
	shouldCacuAcc = false;
	accStep[0] = 0;
	accStep[1] = 0;

	accInterval[0] = 1;
	accInterval[1] = 1;

	accIntervalCount[0] = 1;
	accIntervalCount[1] = 1;

	setSpeedX(STATIC);
	setSpeedY(STATIC);
}

void GameObjWithAnim::setAnimInterval(uint8_t interval){
	if(Anim != nullptr)
		Anim->setInterval(interval);
}

void GameObjWithAnim::setAnimStatus(AnimPlayStatus status){
	if(Anim != nullptr)
		Anim->setStatus(status);
}

void GameObjWithAnim::setAnimTo(uint8_t index){
	if(Anim != nullptr)
		Anim->AnimSwichTo(index);
}

void Ground::takeMove(uint8_t axisIndex){
	for (const auto& node : SPEED) {
	    if (node.mode == static_cast<SPEED_MODE>(GAME_SPEED[axisIndex])){
	    	currentInterval[axisIndex] = node.interval;
	    	current_loc[axisIndex] += node.step;
	    }
	}
}

void Cactus::takeMove(uint8_t axisIndex){
	for (const auto& node : SPEED) {
	    if (node.mode == static_cast<SPEED_MODE>(GAME_SPEED[axisIndex])){
	    	currentInterval[axisIndex] = node.interval;
	    	current_loc[axisIndex] += node.step;
	    }
	}
}

void Dino::takeMove(uint8_t axisIndex){
	// 加速度是否计算
	if(shouldCacuAcc){
		accIntervalCount[0]--;
		accIntervalCount[1]--;
		if(accIntervalCount[0] == 0)
			speedUpDown(0);
		if(accIntervalCount[1] == 0)
			speedUpDown(1);
	}

	for (const auto& node : SPEED) {
		if (node.mode == static_cast<SPEED_MODE>(speed[axisIndex])){
			// 重设刷新间隔
			currentInterval[axisIndex] = node.interval;
			// 限制y轴刷新范围
			if(axisIndex == 1){
				// 向上超出边界
				uint8_t expected = current_loc[axisIndex] + node.step;
//				if(expected > OLED_ROW){
//					setLocation(getLocationX(), 0);
//					fallDown();
//					return;
//				}
				// 向下超出边界
				if(expected > GROUND_Y && speed[1] > 5){
					current_loc[axisIndex] = OLED_ROW-height;
					resetAccSys();
					isJumping = false;
					setAnimTo(DINO_RUN);
					return;
				}
			}
			current_loc[axisIndex] += node.step;
		}
	}
}

//void Dino::fallDown(){
//	setSpeedY(STATIC);
//	accIntervalCount[1] = 1;
//	accStep[1] = 1;
//	accInterval[1] = 7;
//}

void Dino::jumpUp(){
	if(!isJumping){
		setAnimTo(DINO_JUMP);
		isJumping = true;
		shouldCacuAcc = true;
		setSpeedY(NEGATIVE_SUPER_FAST);
		accStep[1] = 1;
		accInterval[1] = 15;
	}
}

