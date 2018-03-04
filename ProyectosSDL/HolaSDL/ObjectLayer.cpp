#include "ObjectLayer.h"


void ObjectLayer::update(Uint32 time)
{
	GameState::Instance()->update(time);
}

void ObjectLayer::render(Uint32 time)
{
	GameState::Instance()->render(time);
}