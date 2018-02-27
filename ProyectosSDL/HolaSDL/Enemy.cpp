#include "Enemy.h"
#include <iostream>


Enemy::Enemy():player(nullptr), Character()
{

}

Enemy::Enemy(Entity* player, int life):player(player), Character(life)
{
	/*Player* playerComp = player->getComponent<Player>();
	if (playerComp != nullptr)
		cout << "There's a player with life: " << playerComp->getLife();*/
}

void Enemy::update(Entity* o, Uint32 time)
{
	Vector2D pos{ o->getPosition().getX(), o->getPosition().getY() };
	Vector2D playerPos{ player->getPosition().getX(), player->getPosition().getY() };

	//Movimiento en X
	if (pos.getX() < playerPos.getX())
		pos.setX(pos.getX() + 1);
	else if(pos.getX() > playerPos.getX())
		pos.setX(pos.getX() - 1);

	//Movimiento en Y
	if (pos.getY() < playerPos.getY())
		pos.setY(pos.getY() + 1);
	else if (pos.getY()> playerPos.getY())
		pos.setY(pos.getY() - 1);

	//Actualizamos a posicion
	o->setPosition(pos);

	//Lo pilla
	if (pos.getX() == playerPos.getX() && pos.getY() == playerPos.getY())
		cout << "You died" << endl;
	else
		cout << "(" << pos.getX() << "," << pos.getY() << ")" << endl;

}

void Enemy::handleInput(Entity* o, Uint32 time, const SDL_Event& event) {}
void Enemy::render(Entity* o, Uint32 time) {}



Enemy::~Enemy()
{
}
