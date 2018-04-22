#pragma once
#include "GameState.h"
#include "LevelParser.h"
#include "Inventory.h"
//#include "CursorRenderer.h"
//#include "MouseMotionInput.h"
#include <memory>

class MenuState : public GameState {

private:
	SDL_Renderer* pRenderer;
	ResourceManager* resource;

	double width;
	double height;

	MenuState();
	static unique_ptr<MenuState> s_pInstance;

	vector<SDL_Rect> destRect;

public:
	Entity* inventory;
	static MenuState* Instance()
	{
		if (s_pInstance.get() == nullptr)
			s_pInstance.reset(new MenuState());
		return s_pInstance.get();
	}
	~MenuState();
	virtual void startState();
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);
	virtual void handleInput(Uint32 time, SDL_Event& event);
};

typedef MenuState MenuState;
