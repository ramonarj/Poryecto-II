#include "Character.h"



Character::Character() :life(0){}

Character::Character(int life, int damage) : life(life), damage(damage) {};


void Character::update(Entity* o, Uint32 time)
{
	//Solo si est� vivo
	if(isAlive())
		move(o);
}

void Character::takeDamage(int i)
{
	//Si est� vivo solamente
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
