#pragma once
#include "Game.h"
#include "GameState.h"

class PlayState: public GameState {

private:
	SDL_Renderer* renderer;
	
public:
	PlayState() {};
	PlayState(Game* game);
	~PlayState();
};

