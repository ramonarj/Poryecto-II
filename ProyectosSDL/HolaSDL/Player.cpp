#include "Player.h"



Player::Player():Character()
{
}

Player::Player(int life, int damage):Character(life, damage)
{
}

void Player::move(Entity* o)
{
	Vector2D pos = { o->getPosition().getX(), o->getPosition().getY() };

	pos.setX(pos.getX() + o->getVelocity().getX());
	pos.setY(pos.getY() + o->getVelocity().getY());

	o->setPosition(pos);
}

void Player::handleInput(Entity* o, Uint32 time, const SDL_Event& event)
{
	
}

void Player::render(Entity* o, Uint32 time){}

Player::~Player()
{
}
