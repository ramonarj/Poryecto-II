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
	if (thisEntity_ == nullptr)
		thisEntity_ = o;

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
	else
	{
		if (o->getComponent<Player>() != nullptr)
		{
			if (!Game::Instance()->getEntityWithComponent<FadeManager>()->getComponent<FadeManager>()->getDoFade() && Game::Instance()->getEntityWithComponent<FadeManager>()->getComponent<FadeManager>()->getAlphaFade() == 0)
			{
				Game::Instance()->getEntityWithComponent<FadeManager>()->getComponent<FadeManager>()->setDoFade(true, 10);
			}
			else
			{
				if (Game::Instance()->getEntityWithComponent<FadeManager>()->getComponent<FadeManager>()->getAlphaFade() == MAX_FADE_ALPHA)
				{
					o->setPosition(o->getComponent<Player>()->getLastSRPos());
					o->getComponent<Character>()->setAlive();
					o->getComponent<Player>()->setInvincible(false);
					o->getComponent<PlayerAnimationComponent>()->removeTransparency();
				}
			}
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
		if (!isAlive()) {
			cout << "I died" << endl;
			if (thisEntity_->getComponent<Player>() != nullptr && thisEntity_->getIsReading()) {		//Como esta leyendo el ultimo interactible con el que interactuo fue un registro
				thisEntity_->getComponent<KeyBoardInputComponent>()->interactDeadRegister();
				thisEntity_->getComponent<ControllerInputComponent>()->interactDeadRegister();
			}
			if (thisEntity_->getComponent<Player>() != nullptr) {
				if(thisEntity_->getComponent<KeyBoardInputComponent>()->InventoryOpen())
					thisEntity_->getComponent<KeyBoardInputComponent>()->switchOffInv();
				else if (thisEntity_->getComponent<ControllerInputComponent>()->InventoryOpen())
					thisEntity_->getComponent<ControllerInputComponent>()->switchOffInv();
				//Tal vez con mando haya que hacerlo tambien pero es un poco lio mañana lo miro CONTINUAR
			}
		}
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

void Character::knockBack(Entity*o, Vector2D desplazamiento)	//WHEN PUNCHING
{
	if (!o->getComponent<Character>()->getKnockBack()) 
	{
		o->setVelocity(Vector2D(desplazamiento.getX(), -desplazamiento.getY()));
		o->getComponent<Character>()->setKnockBackOn();
		o->getComponent<Character>()->setKnockBack(true);
	}
}

void Character::knockBack(Entity*o, Entity* own, double push)
{
	if (!o->getComponent<Character>()->getKnockBack())
	{
		o->setVelocity(Vector2D(-(o->getDirection().getX()) *push, -(o->getDirection().getY())*push));
		o->getComponent<Character>()->setKnockBackOn();
		o->getComponent<Character>()->setKnockBack(true);
	}
}
