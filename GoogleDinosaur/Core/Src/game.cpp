/*
 * game.cpp
 *
 *  Created on: Jan 31, 2024
 *      Author: zhiyuan
 */
#include "game.hpp"

std::list<speedNode> SPEED = {
				{NEGATIVE_SUPER_FAST,1,-3},
				{NEGATIVE_FAST,1,-2},
				{NEGATIVE_NORMAL,1,-1},
				{NEGATIVE_SLOW,2,-1},
				{NEGATIVE_SUPER_SLOW,3,-1},
				{STATIC, 255, 0},
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
	for (const auto& node : SPEED) {
		if (node.mode == speed[axisIndex]){
			currentInterval[axisIndex] = node.interval;
			current_loc[axisIndex] += node.step;
		}
	}
}


