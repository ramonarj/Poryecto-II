#pragma once
#include "GameState.h"
#include "KeypadComponent.h"
#include "KeyPadController.h"

class KeypadState : public GameState
{
private:
	KeypadState();
	static KeypadState* s_pInstance;
	bool pop_ = false;

public:
	~KeypadState();
	static KeypadState* Instance()
	{
		if (s_pInstance == nullptr)
			s_pInstance = new KeypadState();
		return s_pInstance;
	}

	virtual void startState();
	virtual void render(Uint32 time);
	virtual void update(Uint32 time);
	virtual void handleInput(Uint32 time, SDL_Event& event);
	virtual void resetSingleton() { s_pInstance = nullptr; };

	void setPop(bool b) { pop_ = b; };
	bool getPop() { return pop_; };	
};
	typedef KeypadState KeypadState;

