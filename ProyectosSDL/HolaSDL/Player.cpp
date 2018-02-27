#include "Player.h"



Player::Player()
{
}

Player::Player(int posX, int posY):Character(posX, posY)
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
