#include "Enemy.h"


Enemy::Enemy():player(nullptr)
{

}

Enemy::Enemy(Player* player):player(player)
{

}

void Enemy::update(GameObject* o, Uint32 time)
{

}

void Enemy::handleInput(GameObject* o, Uint32 time, const SDL_Event& event) {}
void Enemy::render(GameObject* o, Uint32 time) {}



Enemy::~Enemy()
{
}
