#include "Player.h"



Player::Player():Character()
{
}

Player::Player(int life):Character(life)
{
}


void Player::update(Entity* o, Uint32 time)
{

}

void Player::handleInput(Entity* o, Uint32 time, const SDL_Event& event){}
void Player::render(Entity* o, Uint32 time){}

Player::~Player()
{
}
