#pragma once
#include "Item.h"

class InsulationTape : public Item
{
public:
	InsulationTape() : Item(ItemType::Insulationtape) {};
	virtual ~InsulationTape();

	virtual void interact(); // M�todo para interactuar de los Itemss
	virtual void useItem(Entity* e);
};

