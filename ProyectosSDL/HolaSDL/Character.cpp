#include "Character.h"



Character::Character() :life(0){}

Character::Character(int life) : life(life) {};


void Character::update(Entity* o, Uint32 time)
{
	move(o);
}

void Character::takeDamage(int i)
{
	life -= i;
}

Character::~Character()
{
}
