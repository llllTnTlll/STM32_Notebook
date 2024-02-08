/*
 * random.h
 *
 *  Created on: 2024年2月8日
 *      Author: zhiyuan
 */

#ifndef INC_RANDOM_HPP_
#define INC_RANDOM_HPP_

#include "adc.h"
#include <random>

class Random{
private:
	std::mt19937 gen;
	uint16_t GetRandomSeed();
public:
	Random(){
		HAL_ADCEx_Calibration_Start(&hadc1);
		gen.seed(GetRandomSeed());
	}
	int16_t getRandomInt16(int16_t begin, int16_t end);
	bool withXPercentProbability(uint8_t prob);
};

#endif /* INC_RANDOM_HPP_ */
