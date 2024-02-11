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
#include <list>

#define TIME_STEP_MS 10

enum SPEED_MODE{
	NEGATIVE_SUPER_FAST,
	NEGATIVE_FAST,
	NEGATIVE_NORMAL,
	NEGATIVE_SLOW,
	NEGATIVE_SUPER_SLOW,
	STATIC,
	POSITIVE_SUPER_SLOW,
	POSITIVE_SLOW,
	POSITIVE_NORMAL,
	POSITIVE_FAST,
	POSITIVE_SUPER_FAST,
};
class GameObj{
protected:
	// 基本属性
	uint8_t width = 0;
	uint8_t height = 0;
	uint8_t current_loc[2] = {0, 0};
	uint8_t currentInterval[2] = {1, 1};
	bool shouldReclaim = false;

	// 速度相关
	SPEED_MODE speed[2] = {STATIC, STATIC};
	struct speedNode{
		SPEED_MODE mode;
		uint8_t interval;
		int8_t step;
		speedNode(SPEED_MODE M, uint8_t i, int8_t s):mode(M),interval(i),step(s){}
	};
	static std::list<speedNode> SPEED;

	void updateReclaimFlag();
	void initProperties();
	virtual void takeMove(uint8_t axisIndex);
public:
	inline void setLocation(uint8_t x, uint8_t y){
		current_loc[0] = x;
		current_loc[1] = y;
	}
	inline virtual void setSpeed(SPEED_MODE speed_x, SPEED_MODE speed_y){
		speed[0] = speed_x;
		speed[1] = speed_y;
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
	inline virtual const Image* getHexImg(){
		return &cloudImg;
	}
	void recalcuProperties();
};

class Cloud : public GameObj{
public:
	Cloud(uint8_t* loc, SPEED_MODE* speed){
		initProperties();
		setLocation(loc[0], loc[1]);
		setSpeed(speed[0], speed[1]);
	}

	inline const Image* getHexImg() override{
		return &cloudImg;
	}
};

class Cactus : public GameObj{
private:
	static SPEED_MODE speed[2];
public:
	Cactus(){
		initProperties();
		setLocation(128, 64-height);
	}
	inline const Image* getHexImg() override{
		return &cactusImg;
	}

	void takeMove(uint8_t axisIndex) override;
	inline void setSpeed(SPEED_MODE speed_x, SPEED_MODE speed_y) override{
		// do nothing
	}
	static void setSpeedALL(SPEED_MODE speed_x, SPEED_MODE speed_y){
		Cactus::speed[0] = speed_x;
		Cactus::speed[1] = speed_y;
	}
};

class Dino : public GameObj{
public:
	Dino(){
		initProperties();
		setLocation(3, 64-height);
		setSpeed(STATIC, STATIC);
	}

	inline const Image* getHexImg() override{
		return &dino1Img;
	}
};

#endif /* INC_GAME_HPP_ */
