#pragma once
#include "Item.h"
#include "checkML.h"


class InsulationTape : public Item
{
public:
	InsulationTape(const string& filename, std::string interactMessage = "") : Item(ItemType::INSULATIONTEPE, filename, interactMessage) {};
	virtual ~InsulationTape();
};

