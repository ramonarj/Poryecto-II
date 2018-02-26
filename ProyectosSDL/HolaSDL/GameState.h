#pragma once
#include "GameObject.h"
#include "Entity.h"
#include <list>

using namespace std;

class Game;

class GameState {

protected:
	list<Entity*> stage;
	Game* game_;

public:
	GameState() {};
	GameState(Game* game);
	virtual ~GameState();
	virtual void render(Uint32 time);
	virtual void update(Uint32 time);
	virtual void handleEvent(Uint32 time, SDL_Event& event);
};

