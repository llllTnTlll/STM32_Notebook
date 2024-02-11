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
#include <string>
#include <algorithm>

class LogicCore{
private:
	// 外挂硬件
	SSD1315 *oled;

	// 容器
	std::vector<GameObj*> backgroundObjs;    //背景物体容器（不参与碰撞运算）
	std::vector<GameObj*> foregroundObjs;    //关键物体容器

	// 随机数生成引擎
    Random *rand;

public:
	LogicCore(){
		oled = new SSD1315(PAGE_MODE);
		rand = new Random();

		Dino *dino = new Dino();
		foregroundObjs.push_back(dino);
	}

	void renewAll();    //将容器中的所有对象的加速度速度以及位置更新至下一帧状态
	void drawAll();     //绘制容器中存储的对象
	void checkAll();    //检查所有物体生命周期 生成或回收对象

	inline void clrScreen(){
		oled->ClearFrame();
	}
	inline void refreshScreen(){
		oled->ShowFrame(true);
	}
	inline void updateFrameRate(){
		oled->UpdateFrameRate();
	}
};

#endif /* INC_LOGIC_CORE_HPP_ */
