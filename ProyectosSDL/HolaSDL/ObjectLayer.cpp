#include "ObjectLayer.h"


void ObjectLayer::update(Level* pLevel, Uint32 time)
{
	m_collisionManager.checkPlayerTileCollision(pLevel->getPlayer(), pLevel->getCollidableLayers());

	GameState::Instance()->update(time);
}

void ObjectLayer::render(Uint32 time)
{
	GameState::Instance()->render(time);
}