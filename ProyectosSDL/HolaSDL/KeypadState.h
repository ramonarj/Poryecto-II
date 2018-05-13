#pragma once
#include "GameState.h"
#include "KeypadComponent.h"
#include "KeyPadController.h"

class KeypadState : public GameState
{
private:
	KeypadState();
	static unique_ptr<KeypadState> s_pInstance;

public:
	~KeypadState();
	static KeypadState* Instance()
	{
		if (s_pInstance.get() == nullptr)
			s_pInstance.reset(new KeypadState());
		return s_pInstance.get();
	}

	virtual void startState();
	virtual void render(Uint32 time);
	virtual void update(Uint32 time);
	virtual void handleInput(Uint32 time, SDL_Event& event);
};
	typedef KeypadState KeypadState;

