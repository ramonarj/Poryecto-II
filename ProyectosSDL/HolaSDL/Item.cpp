#include "Item.h"
#include <iostream>

Item::~Item()
{
}

void Item::update() {

}

void Item::interact() {
	std::cout << "You interacted with: " << type_ << std::endl;
}