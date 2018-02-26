#include "Enemy.h"


Enemy::Enemy():player(nullptr)
{

}

Enemy::Enemy(Player* player):player(player)
{

}

void Enemy::update(GameObject* o, Uint32 time)
{
	//Movimiento en X
	if (player->getPosX() < posX)
		posX++;
	else if(player->getPosX() > posX)
		posX--;

	//Movimiento en Y
	if (player->getPosY() < posY)
		posY++;
	else if (player->getPosX() > posY)
		posX--;

}

void Enemy::handleInput(GameObject* o, Uint32 time, const SDL_Event& event) {}
void Enemy::render(GameObject* o, Uint32 time) {}



Enemy::~Enemy()
{
}
