#include "ObjectLayer.h"


void ObjectLayer::update(Level* pLevel, Uint32 time)
{
	GameState::Instance()->update(time);
}

void ObjectLayer::render(Uint32 time)
{
	GameState::Instance()->render(time);
}

void ObjectLayer::handleInput(Uint32 time, SDL_Event & event)
{
	GameState::Instance()->handleInput(time, event);
}
