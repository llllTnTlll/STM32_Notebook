/*
 * game.cpp
 *
 *  Created on: Jan 31, 2024
 *      Author: zhiyuan
 */
#include "game.hpp"

void GameObj::setLocation(uint8_t x, uint8_t y){
	current_loc[0] = x;
	current_loc[1] = y;
}

void GameObj::refreshObj(){
	uint8_t current_x = current_loc[0] + speed[0] * TIME_STEP + 0.5 * acceleration[0] * std::pow(TIME_STEP, 2);
	uint8_t current_y = current_loc[1] + speed[1] * TIME_STEP + 0.5 * acceleration[1] * std::pow(TIME_STEP, 2);
	setLocation(current_x, current_y);
}

Image Cloud::getHexImg(){
	return cloudImg;
}
