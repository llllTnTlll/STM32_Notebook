/*
 * pid_control.h
 *
 *  Created on: May 12, 2024
 *      Author: zhiyuan
 */

#ifndef INC_PID_CONTROL_HPP_
#define INC_PID_CONTROL_HPP_

#include <cmath>
#include "stdint.h"

typedef struct{
	double Kp, Ki, Kd;
	int32_t current = 0;
	int32_t target = 0;
	int32_t sum_err = 0;
	int32_t last_err = 0;
}PID_Params;

class PID{
private:
	PID_Params params;
	void next_step();
public:
	PID(PID_Params& params){
		this->params = params;
	}

	void set_target(uint32_t target);
	uint32_t get_value();
};


#endif /* INC_PID_CONTROL_HPP_ */
