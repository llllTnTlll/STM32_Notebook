/*
 * logic_core.h
 *
 *  Created on: Jan 31, 2024
 *      Author: zhiyuan
 */

#ifndef INC_LOGIC_CORE_HPP_
#define INC_LOGIC_CORE_HPP_

#include "game.hpp"
#include "oled.hpp"
#include "random.hpp"
#include "keyboard.hpp"
#include <algorithm>
#include <memory>

extern SPEED_MODE GAME_SPEED[2];

class LogicCore{
private:
	// 总分数
	uint16_t Score = 0;

	// 外挂硬件
	SSD1315 *oled;
	KeyBoard *keyboard;

	// 容器
	std::vector<std::shared_ptr<GameObj>> backgroundObjs;    //背景物体容器（不参与碰撞运算）
	std::vector<std::shared_ptr<GameObj>> foregroundObjs;    //关键物体容器
	std::shared_ptr<Dino> mainCharactor;                     //主控角色

	// 随机数生成引擎
    Random *rand;

    // 生成对象数量限制
    uint8_t MaxCloudNum = 2;
    uint8_t MaxCactusNum = 2;

    bool shouldGenerateCloud = true;
    bool shouldGenerateCactus = true;

    bool isGameOver();

public:
	LogicCore(KeyBoard *k){
		keyboard = k;
		oled = new SSD1315(PAGE_MODE);
		rand = new Random();

		std::shared_ptr<Dino> dino(new Dino());
		mainCharactor = dino;

		std::shared_ptr<Ground> ground(new Ground());
		backgroundObjs.push_back(ground);

		setGameSpeed(NEGATIVE_SLOW, STATIC);
	}

	void renewAll();    //将容器中的所有对象的加速度速度以及位置更新至下一帧状态
	void drawAll();     //绘制容器中存储的对象
	void checkAll();    //检查所有物体生命周期 生成或回收对象

	void renewGenerateFlag();

	std::string getTotalScore();
	void updateTotalScore();

	inline void clrScreen(){
		oled->ClearFrame();
	}
	inline void refreshScreen(){
		oled->ShowFrame(true);
	}
	inline void updateFrameRate(){
		oled->UpdateFrameRate();
	}

	inline void setGameSpeed(SPEED_MODE speedX, SPEED_MODE speedY){
		GAME_SPEED[0] = speedX;
		GAME_SPEED[1] = speedY;
	}
};

#endif /* INC_LOGIC_CORE_HPP_ */
