#include "Enemy.h"
#include <iostream>
#include <math.h>


Enemy::Enemy():player(nullptr), Character(){}

Enemy::Enemy(Entity* player, int life, int damage):player(player), Character(life, damage)
{
	Player* playerComp = player->getComponent<Player>();
	if (playerComp != nullptr)
		cout << "There's a player with life: " << playerComp->getLife() << endl;
}

void Enemy::move(Entity* o)
{
	Entity* player = Game::Instance()->getEntityWithComponent<Player>();

	//Si el jugador está vivo
	if(player->getComponent<Player>()->isAlive())
	{
		//Posición del jugador y del enemigo
		Vector2D pos{ o->getPosition().getX(), o->getPosition().getY() };
		Vector2D playerPos{ player->getPosition().getX(), player->getPosition().getY() };

		//Lo persigue
		Vector2D chaseVector{ playerPos.getX() - pos.getX(), playerPos.getY() - pos.getY() };
		float alpha = abs(atan(chaseVector.getY() / chaseVector.getX()));
		int velMag = o->getVelocity().magnitude();

		////Ponemos la nueva velocidad
		//Vector2D vel{ cos(alpha) * velMag * chaseVector.getX() / abs(chaseVector.getX()), sin(alpha)* velMag * chaseVector.getY() / abs(chaseVector.getY()) };
		//cout << vel << endl;
		//o->setVelocity(vel);

		////Actualizamos a posicion(PONER ESTO EN CHARACTER)
		//pos.setX(pos.getX() + o->getVelocity().getX());
		//pos.setY(pos.getY() + o->getVelocity().getY());

		Vector2D vel;
		//Movimiento en X
		if (pos.getX() < playerPos.getX())
			vel.setX(cos(alpha) * velMag);
		else if (pos.getX() > playerPos.getX())
			vel.setX(cos(alpha) * -velMag);

		//Movimiento en Y
		if (pos.getY() < playerPos.getY())
			vel.setY(velMag);
		else if (pos.getY()> playerPos.getY())
			vel.setY(-velMag);

		//cout << alpha << endl;
		o->setVelocity(vel);
		//Actualizamos a posicion(PONER ESTO EN CHARACTER)
		Character::move(o);


		//PROVISIONAL: HACER COLISIONES EN PLAN BIEN
		//Lo pilla
		if ((int)pos.getX() == playerPos.getX() && (int)pos.getY() == playerPos.getY())
		{
			cout << "e";
			//De momento, ambos se hacen daño
			player->getComponent<Player>()->takeDamage(damage);
			this->takeDamage(player->getComponent<Player>()->getDamage());

			//Respawn
			pos.setX(pos.getX() + 30);
			pos.setY(pos.getY() + 30);
			o->setPosition(pos);
		}
	}
	
}

void Enemy::handleInput(Entity* o, Uint32 time, const SDL_Event& event) {}
void Enemy::render(Entity* o, Uint32 time) {}

void Enemy::update(Entity * o, Uint32 time)
{
	//Tanto él como el jugador están vivos
	if (isAlive())
		move(o);
	else
		o->setVelocity(Vector2D(0, 0));
}

Enemy::~Enemy()
{
}
