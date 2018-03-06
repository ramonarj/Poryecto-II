#pragma once
#include "Component.h"

class Character: public Component
{
public:
	Character();
	Character(int life, int damage);
	void takeDamage(int i);
	bool isAlive() { return life > 0; };
	int getDamage() { return damage; };

	void load(int l, int d);
	void lif() { cout << life << endl; };

	virtual void update(Entity* o, Uint32 time);
	virtual ~Character();

protected:
	int life;
	int damage;
	virtual void move(Entity* o)= 0;

};

