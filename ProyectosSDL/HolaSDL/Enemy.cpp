#include "Enemy.h"
#include <iostream>


Enemy::Enemy():player(nullptr), Character(){}

Enemy::Enemy(int life, int damage) : Character(life, damage){}


Enemy::Enemy(Entity* player, int life, int damage):player(player), Character(life, damage)
{
	Player* playerComp = player->getComponent<Player>();
	if (playerComp != nullptr)
		cout << "There's a player with life: " << playerComp->getLife() << endl;
}

void Enemy::move(Entity* o)
{
	cout << "we";
	//Posición del jugador y del enemigo
	Vector2D pos{ o->getPosition().getX(), o->getPosition().getY() };
	Vector2D playerPos{ player->getPosition().getX(), player->getPosition().getY() };

	//Movimiento en X
	if (pos.getX() < playerPos.getX())
		pos.setX(pos.getX() + 1);
	else if (pos.getX() > playerPos.getX())
		pos.setX(pos.getX() - 1);

	//Movimiento en Y
	if (pos.getY() < playerPos.getY())
		pos.setY(pos.getY() + 1);
	else if (pos.getY()> playerPos.getY())
		pos.setY(pos.getY() - 1);

	//Actualizamos a posicion
	o->setPosition(pos);

	//PROVISIONAL: HACER COLISIONES EN PLAN BIEN
	//Lo pilla
	if (pos.getX() == playerPos.getX() && pos.getY() == playerPos.getY())
	{
		//De momento, ambos se hacen daño
		player->getComponent<Player>()->takeDamage(damage);
		this->takeDamage(player->getComponent<Player>()->getDamage());

		//Respawn
		pos.setX(pos.getX() + 20);
		pos.setY(pos.getY() + 20);
		o->setPosition(pos);
	}
	//Lo persigue
	else
		cout << "(" << pos.getX() << "," << pos.getY() << ")" << endl;
}

void Enemy::handleInput(Entity* o, Uint32 time, const SDL_Event& event) {}
void Enemy::render(Entity* o, Uint32 time) {}

void Enemy::update(Entity * o, Uint32 time)
{
	//Tanto él como el jugador están vivos
	if (isAlive() && player != nullptr && player->getComponent<Player>()->isAlive())
		move(o);

	//Si no, se queda quieto
	/*else
		cout << "(" << o->getPosition().getX() << "," << o->getPosition().getY() << ")" << endl;*/
}

Enemy::~Enemy()
{
}
