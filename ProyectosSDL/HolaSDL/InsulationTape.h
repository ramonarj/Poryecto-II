#pragma once
#include "Item.h"

class InsulationTape : public Item
{
public:
	InsulationTape(const string& filename) : Item(ItemType::INSULATIONTEPE,filename) {};
	virtual ~InsulationTape();

	virtual void use(Entity* e);
};

