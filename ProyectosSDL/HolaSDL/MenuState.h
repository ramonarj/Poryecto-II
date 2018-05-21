#pragma once
#include "GameState.h"
#include "LevelParser.h"
#include "Inventory.h"
//#include "CursorRenderer.h"
//#include "MouseMotionInput.h"
#include <memory>
#include "checkML.h"


class MenuState : public GameState {

private:
	bool loading;
	MenuState();
	static MenuState* s_pInstance;
	Texture* loadingTex_;

public:
	static MenuState* Instance()
	{
		if (s_pInstance == nullptr)
			s_pInstance = new MenuState();
		return s_pInstance;
	}
	~MenuState();
	void setLoadingScreen(bool b);

	virtual void startState();
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);
	virtual void resetSingleton() { 
		//delete s_pInstance;
		s_pInstance = nullptr;
	};

	void setMenuMusic(bool b);

};

typedef MenuState MenuState;
