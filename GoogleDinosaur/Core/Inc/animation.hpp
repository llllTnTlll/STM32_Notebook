/*
 * animation.hpp
 *
 *  Created on: 2024年2月14日
 *      Author: zhiyuan
 */

#ifndef INC_ANIMATION_HPP_
#define INC_ANIMATION_HPP_

#include "font.h"
#include <vector>
#include <map>


//class Animation{
//protected:
//	std::vector<const Image*> FrameData;
//	uint8_t TotalFrame = 0;
//	uint8_t FrameNow = 0;
//
//	uint8_t Interval = 0;
//	uint8_t IntervalCount = 0;
//
//	uint8_t Status = 0;
//
////	void addFrameData(const Image* ptr);
//
////	template<class T>
////	void addFrameDataHelper(const T* ptr) {
////		addFrameData(ptr);
////		TotalFrame++;
////	}
//
////	template<class T, class... Args>
////	void addFrameDataHelper(const T* ptr, const Args*... args) {
////		addFrameData(ptr);
////		addFrameDataHelper(args...);
////	}
//public:
////	template<class... Args>
////	Animation(const Args*... args) {
////		addFrameDataHelper(args...);
////	}
//
//	const Image* getHexFrame();
//	void setInterval(uint8_t interval);
//	void setStatus(uint8_t status);
//};

enum AnimPlayStatus{
	PLAY,
	PHASE,
};

class Animation{
protected:
	std::map<uint8_t, std::vector<const Image*>> AnimStorage;    //动画资源库
	std::vector<const Image*> FrameData;                         //当前播放的动画

	uint8_t TotalFrame = 0;
	uint8_t FrameNow = 0;

	uint8_t Interval = 0;
	uint8_t IntervalCount = 0;

	AnimPlayStatus Status = PLAY;
public:
	void AnimSwichTo(uint8_t index);
	const Image* getHexFrame();
	void setInterval(uint8_t interval);
	void setStatus(AnimPlayStatus status);

};

enum DinoAnimStatus{
	DINO_RUN,
	DINO_JUMP,
	DINO_DEAD,
};

class DinoAnim : public Animation{
public:
	DinoAnim(){
		AnimStorage[DINO_RUN] = std::vector<const Image*>{&dinoRun1Img, &dinoRun2Img};
		AnimStorage[DINO_JUMP] = std::vector<const Image*>{&dinoJump1Img};
		AnimStorage[DINO_DEAD] = std::vector<const Image*>{&dinoDead1Img};
		AnimSwichTo(DINO_RUN);
		setInterval(15);
	}
};
#endif /* INC_ANIMATION_HPP_ */
