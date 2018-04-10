#pragma once
#include "GameState.h"
class LightTestState :	public GameState {
public:
	LightTestState(Game* game_);
	~LightTestState();
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);
	virtual void handleInput(Uint32 time, SDL_Event& event);
};

