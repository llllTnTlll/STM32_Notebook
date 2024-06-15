/*
 * pid_control.cpp
 *
 *  Created on: 2024年5月16日
 *      Author: zhiyuan
 */

#include "pid_control.hpp"


void PID::next_step(){
	int32_t err = params.target - params.current;
	// p
	double p_out = err * params.Kp;

	//i
	params.sum_err += err;
	double i_out = params.sum_err * params.Ki;

	//d
	double d_out = params.Kd * (err - params.last_err);

	params.current += static_cast<int32_t>(std::ceil(p_out + i_out + d_out));
	params.last_err = err;
}

void PID::set_target(uint32_t target){
	params.target = target;
}

uint32_t PID::get_value(){
	next_step();
	return params.current;
}
