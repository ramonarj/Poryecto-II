#pragma once
#include "GameObject.h"
#include "Entity.h"
#include <list>

using namespace std;

class Game;

class GameState {

protected:
	list<Entity*> stage_;
	Game* game_;

	GameState() {};
	static GameState* s_pInstance;

public:

	static GameState* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new GameState();
			return s_pInstance;
		}
		return s_pInstance;
	}
	//GameState();
	GameState(Game* game);
	virtual ~GameState();
	virtual void render(Uint32 time);
	virtual void update(Uint32 time);
	virtual void handleInput(Uint32 time, SDL_Event& event);

	void pushEntities(Entity* e) { stage_.push_back(e); };
	list<Entity*> getEntities() { return stage_; };
};


typedef GameState GameState;

