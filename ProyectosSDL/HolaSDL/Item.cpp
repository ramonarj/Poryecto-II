#include "Item.h"
#include <iostream>

Item::~Item()
{
}

void Item::interact() {
	std::cout << "You interacted with: " << type_ << std::endl;
	//cuando coges un item desactivar los componentes de fisica 
}

void Item::useItem(Entity* e) {
	std::cout << "Has usado: " << this->getType() << std::endl;
	//destruir item
}