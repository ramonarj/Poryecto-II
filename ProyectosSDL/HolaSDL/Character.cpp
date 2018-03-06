#include "Character.h"



Character::Character() :life(0){}

Character::Character(int life, int damage) : life(life), damage(damage) {};


void Character::load(int l, int d)
{
	life = l;
	damage = d;
}

void Character::update(Entity* o, Uint32 time)
{
	//Solo si está vivo
	if(isAlive())
		move(o);
}

void Character::takeDamage(int i)
{
	//Si está vivo solamente
	if(isAlive())
	{
		life -= i; //Restamos la vida
		if (!isAlive())
			cout << "I died" << endl;
		else
			cout << "Life: " << life << endl;
	}
}

Character::~Character()
{
}
