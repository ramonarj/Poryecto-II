#pragma once
#include "Layer.h"
#include "GameState.h"

class ObjectLayer : public Layer
{
public:
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);

	void pushEntity(Entity* e) { GameState::Instance()->pushEntities(e); };

};

