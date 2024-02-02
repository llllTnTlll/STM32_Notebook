/*
 * calculate.h
 *
 *  Created on: Nov 15, 2023
 *      Author: zhiyuan
 */

#ifndef INC_CALCULATOR_HPP_
#define INC_CALCULATOR_HPP_

#include <stack>
#include <string>
#include <cstdio>
#include "max7219.hpp"

class Calculator {
	private:
		std::string suffix;            //后缀表达式
		std::string operand;           //显示在屏幕上的数

		std::stack<char> optStack;
		std::stack<float> numStack;

		void addToSuffix(char& c);
		void addToSuffix(std::string& str);

		float getNumStackValue();
		void clrStack();
		bool isNumber(const std::string& str);
		int getLevel(char& opt) const;
		bool doCalcu();
		void resetAll();

		MAX7219 Screen;
	public:
		Calculator();
		//获取输入内容
		void getInput(char opt);
		//获取当前数字缓存区内容
		std::string getOperand() const;
		//设置当前数字缓存区内容
		void setOperand(std::string s);
		//输入数字添加到数字缓存区
		void addOperand(char c);
};

#endif /* INC_CALCULATOR_HPP_ */
