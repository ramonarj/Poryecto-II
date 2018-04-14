
#pragma once
#include "GameState.h"
#include "SlidingPuzzleComponent.h"

class SlidingPuzzle : public GameState
{
private:
	SlidingPuzzle();
	static unique_ptr<SlidingPuzzle> s_pInstance;
public:
	~SlidingPuzzle();

	static SlidingPuzzle* Instance()
	{
		if (s_pInstance.get() == nullptr)
			s_pInstance.reset(new SlidingPuzzle());
		return s_pInstance.get();
	}

	virtual void startState();
	virtual void render(Uint32 time);
	virtual void update(Uint32 time);
	virtual void handleInput(Uint32 time, SDL_Event& event);
};

typedef SlidingPuzzle SlidingPuzzle;

