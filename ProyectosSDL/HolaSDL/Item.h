#pragma once
#include "LogicComponent.h"
enum ItemType{ Stick, Lever, Pipe, Ax, Alcohol, Bandages, FirstAid, GenericChemical, AcidChemical, 
					Acid, Biocide, PiecePuzzle, Card, Key, TapeInsulation, Photo };

class Item : public LogicComponent//, public Observable
{
public:
	Item(ItemType type);
	virtual ~Item();
	virtual void update();
private:
	ItemType type;
};

