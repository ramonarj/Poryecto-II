#pragma once
#include "GameState.h"
#include "LevelParser.h"
#include "Inventory.h"
//#include "CursorRenderer.h"
//#include "MouseMotionInput.h"
#include <memory>

class MenuState : public GameState {

private:
	MenuState();
	static MenuState* s_pInstance;

public:
	static MenuState* Instance()
	{
		if (s_pInstance == nullptr)
			s_pInstance = new MenuState();
		return s_pInstance;
	}
	~MenuState();
	virtual void startState();
	virtual void render(Uint32 time);
};

typedef MenuState MenuState;
