/*
 * menu.hpp
 *
 *  Created on: 2024年5月16日
 *      Author: zhiyuan
 */

#ifndef INC_MENU_HPP_
#define INC_MENU_HPP_

#include "global.h"
#include "pid_control.hpp"
#include <list>
#include <string>

typedef struct{
	uint8_t ITEMS_PER_PAGE = 4;
	uint8_t MARGIN[2] = {0, 0};
	std::list<std::string> Contents;

}MenuOpt;

class Menu{
private:
	MenuOpt options;

public:
	Menu(MenuOpt& options){
		this->options = options;
	}
};

#endif /* INC_MENU_HPP_ */
