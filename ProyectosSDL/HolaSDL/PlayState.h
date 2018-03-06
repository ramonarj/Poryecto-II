#pragma once
#include "GameState.h"
#include "LevelParser.h"
#include "Inventory.h"

class PlayState: public GameState {

private:
	SDL_Renderer* renderer;
	
public:
	PlayState() {};
	PlayState(Game* game);
	~PlayState();
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);
	virtual void handleInput(Uint32 time, SDL_Event& event);
};

