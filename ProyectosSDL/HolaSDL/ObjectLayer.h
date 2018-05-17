#pragma once
#include "Layer.h"
#include "GameState.h"
#include "CollisionManager.h"
#include "Game.h"
#include "checkML.h"


class ObjectLayer : public Layer
{
public:
	virtual void update(Level* pLevel, Uint32 time);
	virtual void render();
	virtual void handleInput(Uint32 time, SDL_Event& event);
};

