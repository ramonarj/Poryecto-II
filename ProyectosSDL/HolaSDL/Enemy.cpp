#include "Enemy.h"
#include <iostream>


Enemy::Enemy():player(nullptr), Character()
{

}

Enemy::Enemy(Player* player, int posX, int posY):player(player), Character(posX, posY)
{

}

void Enemy::update(Entity* o, Uint32 time)
{
	
	//Movimiento en X
	if (posX < player->getPosX())
		posX++;
	else if(posX > player->getPosX())
		posX--;

	//Movimiento en Y
	if (posY < player->getPosY())
		posY++;
	else if (posY > player->getPosY())
		posY--;

	//Lo pilla
	if (posX == player->getPosX() && posY == player->getPosY())
		cout << "You died" << endl;
	else
		cout << "(" << posX << "," << posY << ")" << endl;

}

void Enemy::handleInput(Entity* o, Uint32 time, const SDL_Event& event) {}
void Enemy::render(Entity* o, Uint32 time) {}



Enemy::~Enemy()
{
}
