/*
 * game.hpp
 *
 *  Created on: Jan 31, 2024
 *      Author: zhiyuan
 */

#ifndef INC_GAME_HPP_
#define INC_GAME_HPP_

#include "font.h"
#include <cmath>

#define TIME_STEP_MS 10

class GameObj{
protected:
	uint8_t width = 0;
	uint8_t height = 0;
	uint8_t current_loc[2] = {0, 0};

	int16_t speed[2] = {0, 0};
	int16_t acceleration[2] = {0, 0};
	uint8_t refreshInterval[2] = {0, 0};
	uint8_t step = 2;

	bool shouldReclaim = false;

	void recalcuLoc(uint8_t& currentLoc, uint8_t& refreshInterval, int16_t& speed);
	void updateReclaimFlag();
public:
	inline void setLocation(uint8_t x, uint8_t y){
		current_loc[0] = x;
		current_loc[1] = y;
	}
	inline void setSpeed(int16_t speedX, int16_t speedY){
		speed[0] = speedX;
		speed[1] = speedY;
	}

	inline uint8_t getLocationX(){
		return current_loc[0];
	}
	inline uint8_t getLocationY(){
		return current_loc[1];
	}
	inline bool getReclaimFlag(){
		return shouldReclaim;
	}
	virtual const Image* getHexImg();

	void recalcuProperties();
};


inline const Image* GameObj::getHexImg(){
	// TODO改成一个占位符
	return &cloudImg;
}

class Cloud : public GameObj{
public:
	Cloud(uint8_t* loc, int16_t* speedXY){
		width = 30;
		height = 10;
		speed[0] = 0;
		speed[1] = 0;
		setLocation(loc[0], loc[1]);
		setSpeed(speedXY[0], speedXY[1]);
	}

	const Image* getHexImg() override;
};

inline const Image* Cloud::getHexImg(){
	return &cloudImg;
}
#endif /* INC_GAME_HPP_ */
