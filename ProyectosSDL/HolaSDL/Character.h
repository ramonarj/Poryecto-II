#pragma once
#include "LogicComponent.h"

class Character: public LogicComponent
{
public:
	Character();
	Character(int life);
	virtual ~Character();

protected:
	int life;
};

