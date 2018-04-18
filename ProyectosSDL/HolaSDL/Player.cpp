#include "Player.h"



Player::Player() :Character()
{
}

Player::Player(int life, int damage) : Character(life, damage)
{

}

void Player::move(Entity* o)
{
	Vector2D pos = { o->getPosition().getX(), o->getPosition().getY() };
	Character::move(o);
}

void Player::handleInput(Entity* o, Uint32 time, const SDL_Event& event)
{

}

void Player::render(Entity* o, Uint32 time) {}

Player::~Player()
{
}

void Player::cure() {
	int auxi;
	auxi = int(maxLife_ * cureIndex_);
	life += auxi;
	if (life > maxLife_)
		life = maxLife_;
}