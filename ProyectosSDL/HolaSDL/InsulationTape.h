#pragma once
#include "Item.h"

class InsulationTape : public Item
{
public:
	InsulationTape(const string& filename) : Item(ItemType::Insulationtape,filename) {};
	virtual ~InsulationTape();

	virtual void interact(); // Método para interactuar de los Itemss

	virtual void use(Entity* e);
};

