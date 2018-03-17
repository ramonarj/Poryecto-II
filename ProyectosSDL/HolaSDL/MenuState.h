#pragma once
#include "GameState.h"
#include "LevelParser.h"
#include "Inventory.h"
#include "MenuButton.h"

class MenuState : public GameState {

private:
	SDL_Renderer* pRenderer;
	const Resources* resource;

	double width;
	double height;

	MenuState();
	static MenuState* s_pInstance;

	vector<SDL_Rect> destRect;

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
