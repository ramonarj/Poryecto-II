#pragma once
#include "GameState.h"

class PlayState: public GameState {

private:
	SDL_Renderer* renderer;
	
public:
	PlayState() {};
	PlayState(Game* game);
	~PlayState();
	virtual void render(Uint32 time);
};

