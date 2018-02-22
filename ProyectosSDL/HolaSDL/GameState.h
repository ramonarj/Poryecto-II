#pragma once
#include "GameObject.h"
#include <list>

using namespace std;

class Game;

class GameState {

protected:
	// CLASE POR TERMINAR
	//------- CAMBIAR GAMEOBJECTS POR ETITY EN ESTA CLASE UNA VEZ ESTE TERMINADA LA CLASE ENTITY ------------
	list<GameObject*> stage;
	Game* game_;

public:
	GameState() {};
	GameState(Game* game);
	virtual ~GameState();
	virtual void render(Uint32 time);
	virtual void update();
	virtual void handleEvent(SDL_Event& event);
};

