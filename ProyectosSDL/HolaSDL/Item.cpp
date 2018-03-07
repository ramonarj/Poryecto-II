#include "Item.h"
#include <iostream>
#include "ItemContainer.h"

Item::~Item()
{
}

void Item::interact(Entity* e, ItemContainer* ic) {
	std::cout << "You interacted with: " << type_ << std::endl;
	//cuando coges un item desactivar los componentes de fisica
	ic->addItem(e);
}