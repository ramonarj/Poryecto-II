#pragma once

#include "sdl_includes.h"
#include "checkML.h"


class Level;

class Layer
{
public:

	virtual ~Layer() {}

	virtual void render() = 0;
	virtual void update(Level* pLevel, Uint32 time) = 0;
	virtual void handleInput(Uint32 time, SDL_Event& event) = 0;
};

