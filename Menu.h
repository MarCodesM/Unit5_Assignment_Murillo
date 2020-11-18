#pragma once
#include "MenuItem.h"
#include <vector>
#include <iomanip>
class Menu
{
	public:
		void populateMenu(std::vector<MenuItem>& entireMenu);
		void showMenu(std::vector<MenuItem>& m);
		void acceptOrder(std::vector<MenuItem>& m);
		void showReciept(std::vector<MenuItem>& m, double tip, double foodTotal);
		void payment(double foodTotal, double tip);
		void saveReciept(std::vector<MenuItem>& m, double tip, double foodTotal);
};

