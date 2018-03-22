#pragma once
#include "Component.h"
#include "Entity.h"

class Character: public Component
{
public:
	Character();
	Character(int life, int damage);
	void takeDamage(int i);
	bool isAlive() { return life > 0; };
	int getDamage() { return damage; };
	bool getAttacking() { return attacking; };
	void setAttacking(bool flag) { attacking = flag; };

	void load(int l, int d);
	void lif() { cout << life << endl; };

	virtual void update(Entity* o, Uint32 time);
	virtual ~Character();

protected:
	int life;
	int damage;
	bool attacking = false;
	virtual void move(Entity* o);
	
};

