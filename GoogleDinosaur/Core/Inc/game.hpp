/*
 * game.hpp
 *
 *  Created on: Jan 31, 2024
 *      Author: zhiyuan
 */

#ifndef INC_GAME_HPP_
#define INC_GAME_HPP_


#include "animation.hpp"
#include "global.h"
#include <cmath>
#include <list>
#include <algorithm>
#include <map>

#define TIME_STEP_MS 10
#define GROUND_Y 38

extern SPEED_MODE GAME_SPEED[2];

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

	// 加速度相关
	bool shouldCacuAcc = false;
	int8_t accStep[2] = {0, 0};
	uint8_t accInterval[2] = {10, 10};
	uint8_t accIntervalCount[2] = {1, 1};

	virtual void updateReclaimFlag();
	void initProperties();
	virtual void takeMove(uint8_t axisIndex);
	void speedUpDown(uint8_t axisIndex);
	void resetAccSys();
public:
	inline void setLocation(uint8_t x, uint8_t y){
		current_loc[0] = x;
		current_loc[1] = y;
	}

	inline virtual void setSpeedX(SPEED_MODE speed_x){
		speed[0] = speed_x;
	}
	inline virtual void setSpeedY(SPEED_MODE speed_y){
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
	virtual void recalcuProperties();
};

class GameObjWithAnim : public GameObj{
protected:
	Animation* Anim = nullptr;
public:
	virtual const Image* getHexImg() override{
		return Anim->getHexFrame();
	}
	void setAnimInterval(uint8_t interval);
	void setAnimStatus(AnimPlayStatus status);
	void setAnimTo(uint8_t index);
};

class Ground : public GameObj{
public:
	Ground(){
		height = 5;
		width = 255;
		setLocation(0, OLED_ROW-height);
	}
	inline const Image* getHexImg() override{
		return &groundImg;
	}

	void updateReclaimFlag() override{
		// 永不销毁
		shouldReclaim = false;
	}

	void takeMove(uint8_t axisIndex) override;
};

class Cloud : public GameObj{
public:
	Cloud(uint8_t* loc, SPEED_MODE* speed){
		initProperties();
		setLocation(loc[0], loc[1]);
		setSpeedX(speed[0]);
		setSpeedY(speed[1]);
	}

	inline const Image* getHexImg() override{
		return &cloudImg;
	}
};

class Cactus : public GameObj{
public:
	Cactus(){
		initProperties();
		setLocation(128, 64-height);
	}
	inline const Image* getHexImg() override{
		return &cactusImg;
	}

	void takeMove(uint8_t axisIndex) override;

};

class Dino : public GameObjWithAnim{
private:
	bool isJumping = false;
public:
	Dino(){
		Anim = new DinoAnim();
		initProperties();
		setLocation(0, GROUND_Y);
	}
	void jumpUp();
	void fallDown();
	void takeMove(uint8_t axisIndex) override;
	inline bool getJumpFlag(){
		return isJumping;
	}
};

#endif /* INC_GAME_HPP_ */
