#pragma once
#include "LogicComponent.h"

class Character: public LogicComponent
{
public:
	Character();
	Character(int posX, int posY);
	int getPosX() { return posX; };
	int getPosY() { return posY; };
	virtual ~Character();
protected:
	int posX, posY;
};

