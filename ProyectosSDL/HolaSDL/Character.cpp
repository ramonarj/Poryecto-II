#include "Character.h"
#include "Player.h"


Character::Character() :life(0), damage(0), knockBack_(false), knockBackOn_(0), knockBackTime_(50){}


void Character::load(int l, int d)
{
	maxLife_ = life = l;
	damage = d;
}

void Character::update(Entity* o, Uint32 time)
{
	//Solo si está vivo
	if (isAlive())
	{
		move(o);
		if (o->getComponent<Character>()->getKnockBack() && (o->getComponent<Character>()->getKnockBackOn() + knockBackTime_ < time))
		{
			o->getComponent<Character>()->setKnockBack(false);
			o->setVelocity(Vector2D(0.0, 0.0));
		}
	}
}

void Character::saveToFile()
{
	
}

void Character::loadToFile(ifstream& file)
{
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
	if (!o->getComponent<Character>()->getKnockBack()) 
	{
		o->setVelocity(Vector2D(desplazamiento.getX(), -desplazamiento.getY()));
		o->getComponent<Character>()->setKnockBackOn();
		o->getComponent<Character>()->setKnockBack(true);
		if (o->getComponent<Player>() != nullptr)
			o->getComponent<Player>()->startInvincible();
	}
}
