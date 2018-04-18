#include "Character.h"



Character::Character() :life(0){}

Character::Character(int life, int damage) : life(life), damage(damage) {};


void Character::load(int l, int d)
{
	maxLife_ = life = l;
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

void Character::move(Entity * o)
{
	Vector2D pos = { o->getPosition().getX(), o->getPosition().getY() };

	pos.setX(pos.getX() + o->getVelocity().getX());
	pos.setY(pos.getY() + o->getVelocity().getY());

	o->setPosition(pos);
}

void Character::knockBack(Entity*o, Vector2D desplazamiento)
{
	o->setPosition(Vector2D
	(o->getPosition().getX() + desplazamiento.getX(),
		o->getPosition().getY() + desplazamiento.getY()));
}
