#include "Player.h"



Player::Player()
{
}

Player::Player(int posX, int posY):Character(posX, posY)
{
}


void Player::update(GameObject* o, Uint32 time)
{

}

void Player::handleInput(GameObject* o, Uint32 time, const SDL_Event& event){}
void Player::render(GameObject* o, Uint32 time){}

Player::~Player()
{
}
