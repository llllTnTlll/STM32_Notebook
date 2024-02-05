/*
 * game.cpp
 *
 *  Created on: Jan 31, 2024
 *      Author: zhiyuan
 */
#include "game.hpp"

void GameObj::recalcuLoc(uint8_t& currentLoc, uint8_t& refreshInterval, int16_t& speed){
	if (refreshInterval == 0 && speed != 0){
		// 保证最小刷新间隔为1
		refreshInterval = std::fmax(1, static_cast<uint8_t>(ceil(1000 / std::abs(speed) / TIME_STEP_MS)));
		if (speed > 0)
			currentLoc -= step;
		if (speed < 0)
			currentLoc -= step;
	}
}

void GameObj::updateReclaimFlag(){
	if(current_loc[0] > 128 && current_loc[0] < 256-width){
		shouldReclaim = true;
	}
}

void GameObj::recalcuProperties(){
	if(!shouldReclaim){
		//重新计算速度

		//更新refreshInterval
		recalcuLoc(current_loc[0], refreshInterval[0], speed[0]);
		recalcuLoc(current_loc[1], refreshInterval[1], speed[1]);

		refreshInterval[0]--;
		refreshInterval[1]--;
	}

	//判断该对象是否已经失效
	//在该游戏中物体一旦越过左侧边界即被视为失效
	updateReclaimFlag();
}
