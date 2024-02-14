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

typedef enum{
	PAUSE,
	PLAY,
}ANIM_STATUS;

class Animation{
private:
	std::vector<const Image*> FrameData;
	uint8_t TotalFrame = 0;
	uint8_t FrameNow = 0;

	uint8_t Interval = 0;
	uint8_t IntervalCount = 0;

	ANIM_STATUS Status = PAUSE;

	void addFrameData(const Image* ptr);

	template<class T>
	void addFrameDataHelper(const T* ptr) {
		addFrameData(ptr);
		TotalFrame++;
	}

	template<class T, class... Args>
	void addFrameDataHelper(const T* ptr, const Args*... args) {
		addFrameData(ptr);
		addFrameDataHelper(args...);
	}
public:
	template<class... Args>
	Animation(const Args*... args) {
		addFrameDataHelper(args...);
	}

	const Image* getHexFrame();
	void setInterval(uint8_t interval);
	void setStatus(ANIM_STATUS status);
};


#endif /* INC_ANIMATION_HPP_ */
