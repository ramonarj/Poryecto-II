#pragma once
#include "GameState.h"
#include "LevelParser.h"
#include "Inventory.h"

class MenuState : public GameState {

private:
	SDL_Renderer* renderer;
	MenuState();
	static MenuState* s_pInstance;
public:
	Entity* inventory;
	static MenuState* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new MenuState();
			return s_pInstance;
		}
		return s_pInstance;
	}
	//PlayState();
	~MenuState();
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);
	virtual void handleInput(Uint32 time, SDL_Event& event);
};

typedef MenuState MenuState;
