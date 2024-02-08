/*
 * random.c
 *
 *  Created on: 2024年2月8日
 *      Author: zhiyuan
 */

#include <random.hpp>


uint16_t Random::GetRandomSeed(){
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 10);
	uint16_t seed = HAL_ADC_GetValue(&hadc1);
	HAL_ADC_Stop(&hadc1);
	return seed;
}

int16_t Random::getRandomInt16(int16_t begin, int16_t end){
	std::uniform_int_distribution<int16_t> dis(begin, end);
	return dis(gen);
}

bool Random::withXPercentProbability(uint8_t prob){
	if(getRandomInt16(0, 100) <= prob)
		return true;
	return false;
}
