#pragma once
#include <iostream>


class MenuItem
{
	private:
		std::string name;
		double itemCost;
		std::string desc;
		char addLetter;
		char removeLetter;
		int count;
	public:
		void setName(std::string n);
		void setItemCost(double c);
		void setDesc(std::string d);
		void setAddLetter(char l);
		void setRemoveLetter(char l);
		void setCount(int c);

		std::string getName();
		std::string getDesc();
		double getItemCost();
		char getAddLetter();
		char getRemoveLetter();
		int getCount();
};

