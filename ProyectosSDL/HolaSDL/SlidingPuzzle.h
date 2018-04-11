
#pragma once
#include "GameState.h"

class SlidingPuzzle : public GameState
{
private:
	SlidingPuzzle();
	static unique_ptr<SlidingPuzzle> s_pInstance;
	void init();
public:
	~SlidingPuzzle();

	static SlidingPuzzle* Instance()
	{
		if (s_pInstance.get() == nullptr)
			s_pInstance.reset(new SlidingPuzzle());
		return s_pInstance.get();
	}

	virtual void startState();
};

typedef SlidingPuzzle SlidingPuzzle;

