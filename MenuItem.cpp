#include "MenuItem.h"


void MenuItem::setName(std::string n)
{
	name = n;
}
void MenuItem::setItemCost(double c)
{
	itemCost = c;
}
void MenuItem::setDesc(std::string d)
{
	desc = d;
}
void MenuItem::setAddLetter(char l)
{
	addLetter = l;
}
void MenuItem::setRemoveLetter(char l)
{
	removeLetter = l;
}
void MenuItem::setCount(int c)
{
	count = c;
}

std::string MenuItem::getName()
{
	return name;
}
std::string MenuItem::getDesc()
{
	return desc;
}
double MenuItem::getItemCost()
{
	return itemCost;
}
char MenuItem::getAddLetter()
{
	return addLetter;
}
char MenuItem::getRemoveLetter()
{
	return removeLetter;
}
int MenuItem::getCount()
{
	return count;
}
