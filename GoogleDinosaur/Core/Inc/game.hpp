/*
 * game.hpp
 *
 *  Created on: Jan 31, 2024
 *      Author: zhiyuan
 */

#ifndef INC_GAME_HPP_
#define INC_GAME_HPP_

#include "font.h"
#include "math.h"

#define TIME_STEP 20

class GameObj{
private:
	void checkLifeCircle();
protected:
	uint8_t width = 0;
	uint8_t height = 0;
	uint8_t current_loc[2] = {0, 0};

	uint8_t speed[2] = {0, 0};
	uint8_t acceleration[2] = {0, 0};
public:
	void setLocation(uint8_t x, uint8_t y);
	void refreshObj();
	virtual Image getHexImg();
};

class Cloud : public GameObj{
public:
	Cloud(uint8_t x, uint8_t y){
		width = 30;
		height = 10;
		speed[0] = -3;
		speed[0] = 0;
		setLocation(x, y);
	}

	Image getHexImg() override;
};
#endif /* INC_GAME_HPP_ */
