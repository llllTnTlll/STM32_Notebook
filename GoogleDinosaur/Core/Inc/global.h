/*
 * global.h
 *
 *  Created on: 2024年2月16日
 *      Author: zhiyuan
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

// OLED参数
#define OLED_PAGE 8            // OLED页数
#define OLED_ROW 8 * OLED_PAGE // OLED行数
#define OLED_COLUMN 128        // OLED列数

typedef enum {
	NEGATIVE_SUPER_FAST,
	NEGATIVE_FAST,
	NEGATIVE_NORMAL,
	NEGATIVE_SLOW,
	NEGATIVE_SUPER_SLOW,
	STATIC,
	POSITIVE_SUPER_SLOW,
	POSITIVE_SLOW,
	POSITIVE_NORMAL,
	POSITIVE_FAST,
	POSITIVE_SUPER_FAST,
}SPEED_MODE;

typedef enum{
	Axis_X,
	Axis_Y
}AXIS_INDEX;

#endif /* INC_GLOBAL_H_ */
