/*
 * animation.cpp
 *
 *  Created on: 2024年2月14日
 *      Author: zhiyuan
 */
#include "animation.hpp"

void Animation::addFrameData(const Image* ptr){
	FrameData.push_back(ptr);
}

void Animation::setInterval(uint8_t interval){
	Interval = interval;
}

void Animation::setStatus(ANIM_STATUS status){
	Status = status;
}

const Image* Animation::getHexFrame(){
	const Image* framePtr = FrameData.at(FrameNow);
	switch(Status){
	case PLAY:{
		if(IntervalCount == 0){
			FrameNow = (FrameNow + 1 > TotalFrame) ? 0 : FrameNow + 1;
			IntervalCount = Interval;
		}
		IntervalCount--;
	}
	case PAUSE:{
		// do nothing
	}
	}
	return framePtr;
}
