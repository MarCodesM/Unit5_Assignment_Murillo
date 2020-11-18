#include <vector>
#include <iostream>
#include "Menu.h"
#include "MenuItem.h"

int main()
{
	std::vector<MenuItem> wholeMenu;
	Menu m;
	m.populateMenu(wholeMenu); //put some default values in the menu
	m.showMenu(wholeMenu); //print the current data of the menu on screen 
	m.acceptOrder(wholeMenu);

	return 0;
}