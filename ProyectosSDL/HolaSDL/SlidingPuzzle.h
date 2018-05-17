
#pragma once
#include "GameState.h"
#include "SlidingPuzzleComponent.h"
#include "SlidingPuzzleController.h"

class SlidingPuzzle : public GameState
{
private:
	SlidingPuzzle();
	static SlidingPuzzle* s_pInstance;
	bool pop_ = false;

public:
	~SlidingPuzzle();

	static SlidingPuzzle* Instance()
	{
		if (s_pInstance == nullptr)
			s_pInstance = new SlidingPuzzle();
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

typedef SlidingPuzzle SlidingPuzzle;

