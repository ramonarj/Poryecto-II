#pragma once
#include "Item.h"

class InsulationTape : public Item
{
public:
	InsulationTape(const string& filename, std::string interactMessage = "") : Item(ItemType::INSULATIONTEPE, filename, interactMessage) {};
	virtual ~InsulationTape();

	virtual void use(Entity* e);
};

