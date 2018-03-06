#pragma once

#include "sdl_includes.h"

class Level;

class Layer
{
public:

	virtual ~Layer() {}

	virtual void render(Uint32 time) = 0;
	virtual void update(Level* pLevel, Uint32 time) = 0;
	virtual void handleInput(Uint32 time, SDL_Event& event) = 0;
};

