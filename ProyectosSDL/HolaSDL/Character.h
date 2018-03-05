#pragma once
#include "Component.h"

class Character: public Component
{
public:
	Character();
	Character(int life);
	void takeDamage(int i);
	bool isAlive() { return life > 0; };


	virtual void update(Entity* o, Uint32 time);
	virtual ~Character();

protected:
	int life;
	virtual void move(Entity* o)= 0;
};

