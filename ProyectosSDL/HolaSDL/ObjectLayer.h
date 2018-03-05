#pragma once
#include "Layer.h"
#include "GameState.h"
#include "CollisionManager.h"
#include "Game.h"

class ObjectLayer : public Layer
{
public:
	virtual void update(Level* pLevel, Uint32 time);
	virtual void render(Uint32 time);

	CollisionManager m_collisionManager;

	void pushEntity(Entity* e) { GameState::Instance()->pushEntities(e); };

};

